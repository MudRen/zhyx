//3�л�ѧ�����������о��ͷ��йء�
#include <ansi.h>
#include <combat.h>

#define ZHEN "��" HIR "����Ǭ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;
		int damage;

        /*if (userp(me) && ! me->query("can_perform/qujing-gunfa/zhen"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
                */

        if (! target) target = offensive_target(me);
		
		weapon = me->query_temp("weapon"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "club")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHEN "��\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")
                return notify_fail("��û�м���ȡ������������ʩչ" ZHEN "��\n");

        if(me->query_skill("qujing-gunfa", 1) < 200 )
                return notify_fail("��ȡ������������죬����ʩչ" ZHEN "��\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("����ڹ���Ϊ����������ʩչ" ZHEN "��\n");

        if( (int)me->query("max_neili") < 4500 )
                return notify_fail("���������Ϊ̫��������ʩչ" ZHEN "��\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("�����ڵ�����̫��������ʩչ" ZHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

			  
        msg = HIW "$N" HIW "������" + weapon->name() + HIW "����ѹ��$n"
              HIW "�������������ŷ���֮��������ȡ������ɱ�š�" HIR "��"
              "��Ǭ��" HIW "����\nֻ�����˾�ȫ���ϵ������֣�" +
              weapon->name() + HIW "����ǧ�ٸ����ƣ�������������" HIW"$n" HIW"�ҳ������У�\n" NOR;			  

        ap = me->query_skill("club") + me->query_skill("force") + me->query_skill("buddhism" ,1) / 2;
        dp = target->query_skill("parry") + target->query_skill("force");
		damage = ap / 2 + random(ap/2);


		msg += HIM"       ���������޸���\n"  NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);            
        
		msg += HIR "       ���¶�������\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);     
								   
		msg += HIY"       ��ǧ�������\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);     								   
					
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        return 1;
}


