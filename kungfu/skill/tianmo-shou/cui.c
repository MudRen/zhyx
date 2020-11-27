// cui.c �߻�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/tianmo-shou/cui"))
                return notify_fail("�㻹����ʹ�á��߻꡹������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("���߻꡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�ܿ���ʹ�á��߻꡹������\n");

        ap = me->query_skill("tianmo-shou", 1);

        if (ap < 150)
                return notify_fail("�����ħ�ֵȼ�����, �޷�ʹ�á��߻꡹��\n");

        if (me->query("neili") < 150)
                return notify_fail("��������������޷����á��߻꡹��\n");

        msg = HIR "$N" HIR "�������䣬���Һ����������������������˫����$n" HIR
              "�����ĵ���\n" NOR;

        dp = target->query_skill("parry", 1);
        if (dp < 1)  dp = 1;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                me->add("neili", -120);
                damage = ap + (int)me->query_skill("force", 1);
                damage = damage / 2 + random(damage / 2);
                target->receive_damage("jing", damage/3, me);
                target->receive_wound("jing", damage/5, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "���Ծ��ɣ��������ܣ���ʱ��"
                                           "�ĸ����š��ٸо��񲻼ã�ҡҡ������\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                me->add("neili", -50);
                msg += CYN "$n" CYN "���������죬����һ�񣬷���������$N"
                       CYN "��һ�С�\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

