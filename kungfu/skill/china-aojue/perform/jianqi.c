#include <ansi.h>
#include <combat.h>

#define JIANQI "��" HIG "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;       
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/china-aojue/jianqi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIANQI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JIANQI "��\n");

        if ((int)me->query_skill("china-aojue", 1) < 350)
                return notify_fail("����л�����������죬����ʩչ" JIANQI "��\n");

        if (me->query("neili") < 800)
                return notify_fail("��������������������ʩչ" JIANQI "��\n");

        if (me->query_skill_mapped("sword") != "china-aojue") 
                return notify_fail("��û�м����л�����Ϊ����������ʩչ" JIANQI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");       

        damage = me->query_skill("china-aojue", 1) + me->query_skill("martial-cognize", 1) + me->query_skill("sword", 1) + me->query_skill("idle-force", 1);
		damage = damage * 3 / 2 + random(damage);
        
        msg = HIW "$N"HIW"���Ӿ������۳���֮�ϣ���Ȼ�̳�������������㽻�������Ƴ���������\n"
              HIW "���ϲ�������ŭ����ӿ��ӭ��" HIW"$n��" HIW"�����л���������ʽ��"HIY"������������\n\n"NOR;

        msg += HIG "$N" HIG "��ǰһ����һ��ֱ��$n���ţ���"
              "�ް�㻨�ɿ��ԡ�\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                   HIR "$n" HIR "�����мܣ����ι������ޣ������̸����š�\n" NOR);            
        
         msg += MAG "\n������$N" MAG "���ὣ����ɨ$nС������ʽ"
              "�����ޱȡ�\n" NOR; 
         msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                   HIR "$n" HIR "�������ã���ʱ��$N"HIR"�������ˡ�\n" NOR);
                                   
        msg += HIC "\n�漴�ּ�$N" HIC "����һԾ��һ������ֱ��$n���̣���ʽ"
              "�����ޱȡ�\n" NOR; 
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   HIR "$n" HIR "�Ṧ��Ƿ���һ��������Ȼ���С�\n" NOR);
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        me->add("neili", -600);
        
       
                                   
         
       /*
        if (ap * 4 / 5 + random(ap) > dp)
        {
              damage = ap*2 + random(ap);
              target->receive_damage("qi", damage * 3 / 2, me);
              target->receive_wound("qi", damage, me);
              msg += HIR "$n" HIR "�����мܣ����ι������ޣ������̸����š�\n" NOR;
              str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";

        } else
        {
                msg += HIC "ֻ��$n" HIC "�����ֵ���Ӳ������$N"
                           "��һ�е��˻�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);

       //�ڶ��У���������ڹ�
        dp = target->query_skill("force", 1);     
        msg = MAG "������$N" MAG "���ὣ����ɨ$nС������ʽ"
              "�����ޱȡ�\n" NOR; 
       
        if (ap * 4 / 5 + random(ap) > dp)
        {       
                damage = ap * 2 + random(ap);
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "�������ã���ʱ��$N�������ˡ�\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";
        } else
        {
                msg += HIC "����$n" HIC "�������˲�����˵��һ������"
                       "��$N���������硣\n" NOR;
        }
        message_combatd(msg, me, target);

       //�����У���������Ṧ
        dp = target->query_skill("dodge", 1); 
    
        msg = HIC "�漴�ּ�$N" HIC "����һԾ��һ������ֱ��$n���̣���ʽ"
              "�����ޱȡ�\n" NOR; 

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 2 + random(ap);
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "�Ṧ��Ƿ���һ��������Ȼ���С�\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";
        } else
        {
                msg += HIC "����$n" HIC "�Ṧ��������׼$N�佣��λ��"
                       "��������Ʈ�����ɣ����˹�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(3 + random(4));  */

        return 1;
}

