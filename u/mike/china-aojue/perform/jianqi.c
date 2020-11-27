#include <ansi.h>
#include <combat.h>

#define JIANQI "��" HIG "�����л�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
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

        if ((int)me->query_skill("china-aojue", 1) < 250)
                return notify_fail("����л�����������죬����ʩչ" JIANQI "��\n");

        if (me->query("neili") < 800)
                return notify_fail("��������������������ʩչ" JIANQI "��\n");

        if (me->query_skill_mapped("sword") != "china-aojue") 
                return notify_fail("��û�м����л�����Ϊ����������ʩչ" JIANQI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -800);

        ap = me->query_skill("china-aojue", 1);
        damage = ap + random(ap);


       //��һ�У���������м�       
        dp = target->query_skill("parry", 1);     

        msg = HIG "$N" HIG "��ǰһ����һ��ֱ��$n���ţ���"
              "�ް�㻨�ɿ��ԡ�\n" NOR; 
       
        if (ap * 4 / 5 + random(ap) > dp)
        {
              damage = ap + random(ap);
              target->receive_damage("qi", damage * 3 / 2, me);
              target->receive_wound("qi", damage, me);
              msg += HIR "$n" HIR "�����мܣ����ι������ޣ������̸����š�\n" NOR;

        } else
        {
                msg += HIC "ֻ��$n" HIC "�����ֵ���Ӳ������$N"
                           "��һ�е��˻�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);

       //�ڶ��У���������ڹ�
        dp = target->query_skill("force", 1);     
        msg = HIG "������$N" HIG "���ὣ����ɨ$nС������ʽ"
              "�����ޱȡ�\n" NOR; 
       
        if (ap * 4 / 5 + random(ap) > dp)
        {       
                damage = ap + random(ap / 2);
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "�������ã���ʱ��$N�������ˡ�\n" NOR;
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
                damage = ap + random(ap / 3);
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "�Ṧ��Ƿ���һ��������Ȼ���С�\n" NOR;
        } else
        {
                msg += HIC "����$n" HIC "�Ṧ��������׼$N�佣��λ��"
                       "��������Ʈ�����ɣ����˹�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(3 + random(4));

        return 1;
}

