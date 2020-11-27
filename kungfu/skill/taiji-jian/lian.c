// lian.c ̫�������������־�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count, acter;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("̫�������������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("taiji-jian", 1) < 120)
                return notify_fail("���̫������������죬����ʹ�á������־���\n");

        if (me->query("neili") < 250)
                return notify_fail("��������������޷�ʹ�á������־���\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��û�м���̫���������޷�ʹ�á������־���\n");

        msg = HIY "$N" HIY "ʹ��̫�������������־�������һ����ԲȦ����$n"
              HIY "Ȧ�ڵ��С�\n" NOR;

        dp = (target->query_skill("force", 1) +
              target->query_skill("parry", 1) +
              target->query_skill("martial-cognize", 1)) / 3;

        if (me->query("character") == "��������" || me->query("character") == "������")
             acter = 3;
        else
             acter = 4;

        ap = (me->query_skill("taiji-shengong", 1) +
              me->query_skill("taiji-jian", 1) +
              me->query_skill("martial-cognize", 1) +
              me->query_skill("taoism", 1)) / acter;

        attack_time = 5;
        if (random(ap) > dp / 2 || !living(target))
        {
                msg += HIC "���$p" HIC "��$P" HIC
                       "���˸����ֲ������������˲�Ͼ��\n" NOR;
                count = ap / 3;
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "�⼸���������������Ҵ��⣬С��Ӧ����\n" NOR;
                count = 0;
        }
                
        me->add_temp("apply/attack", count);
        message_combatd(msg, me, target);

        if (attack_time > 10)    attack_time = 10;

        me->add("neili", -attack_time * 20);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))   break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(2 + random(3));

        return 1;
}

