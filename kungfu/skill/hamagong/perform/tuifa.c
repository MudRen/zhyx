// tui.c ����ʽ֮��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        int n,damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��󡹦������ʽ��֮��ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( objectp(me->query_temp("weapon")) )
	         return notify_fail("���ֱֳ������޷�ʩչ��󡹦�ľ�����\n");
	         
	      if (!(int)me->query_temp("tuitimes"))
                return notify_fail("������������󡹦�ġ�����ʽ���ˡ�\n");
      
        n=me->query_temp("tuitimes");        
                
        msg = HIY"$N"HIY"����󡱵Ĵ�������������󡹦������˫��һ��˫���뷢����ǰ�Ƴ�......\n"
              HIG"��һ��ʵ��$N"HIG"��������֮���ۣ�$n��Ȼ���ܵ�ɽ�麣Х��ľ���Ϯ����\n" NOR;   
        msg += HIM"$N"HIM"��һ�Ƹ��꣬�ڶ�������Ѹ���쳣�ĸϵ���ǰ��δ˥���󾢼�����һ������"HIG""+chinese_number(n)+HIG""HIM"�Ρ�\n" NOR;
        
        damage = me->query_skill("force")* n;
        damage += random(damage/2);
		
		if (n>10)
		{
		     msg +=  HIR "$n" HIR "�����͵�������$N" HIR "�����ƺεȺƴ�$n"HIR"�³�һ����Ѫ����ͬ���ߵķ��ݰ���˳�ȥ��\n" NOR;		
		     target->receive_wound("qi", damage, me);
			 str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));			
			 msg += "($n"+str+")\n";
		}
		else
		{        
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage,100,
                                         HIR "$n" HIR "�����͵�������$N" HIR "�����ƺ�"
                                         "�Ⱥƴ�$n" HIR "��ʱ������Ѫ���������ۡ���"
                                          "�³���һ����Ѫ��\n" NOR);
		}
        
        
        message_combatd(msg, me, target);
        me->delete_temp("tuitimes");
        me->start_busy(2+random(4));
        return 1;
}
