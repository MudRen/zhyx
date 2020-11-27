#include <ansi.h>

inherit F_SSERVER;

#define LEI "��" HIY "��������" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
        object weapon;
 
        
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(LEI "ֻ����ս���жԶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "hammer")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" LEI "��\n");
                
        if ((int)me->query("neili") < 800)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("leiting-fu", 1) < 220)
                return notify_fail("�����������򲻹����޷�ʩչ" LEI "��\n");

        if ((int)me->query_skill("force") < 340)
                return notify_fail("����ڹ���Ϊ�������޷�ʩչ" LEI "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
              
       weapon = me->query_temp("weapon");

        msg = HIC "\n$N" HIC "һ�����ȣ�����"+weapon->name()+HIC"���һ����⣬Я�������֮��ѹ��$n��\n" NOR;
              

        ap = me->query_skill("hammer") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 6;
                msg += HIY "$n" HIY "��$P" HIY "��һ�б仯Ī�⣬�����"
                       "�������ɴ��һ��������������������\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����С��$P" HIC
                       "�����У���Ų������С���мܡ�\n" NOR;
                count = ap / 12;
        }

        message_sort(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -400);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(5));
        me->add_temp("apply/attack", -count);

        return 1;
}

