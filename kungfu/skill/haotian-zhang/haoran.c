// haoran.c ��Ȼһ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ȼһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("haotian-zhang", 1) < 60)
                return notify_fail("�������Ʋ�����죬����ʹ�ú�Ȼһ����\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ��Ȼһ����\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�����������������޷�ʹ�ú�Ȼһ����\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("������û�м�������Ʒ����޷�ʹ�ú�Ȼһ����\n");

        if (me->query_temp("weapon"))
                return notify_fail("�������ֲ��ܹ�ʹ�ú�Ȼһ����\n");

        msg = HIC "$N" HIC "���һ����������$n" HIC "���ϣ�˫��"
              "ͬʱ����������һ�С���Ȼһ������\n" NOR;

        if (living(target))
                dp = target->query_skill("force") / 2;
        else    dp = 0;

        if (random(me->query_skill("force")) > dp)
        {
                me->start_busy(2);
                me->add("neili", -110);
                damage = me->query_skill("strike");
                damage = damage / 3 + random(damage / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "���$p" HIR "��$P" HIR "��������"
                                           "�㣬��æ���ˣ������$P" HIR "һ�ƻ�"
                                           "�˸����У���Ѫ��ֹ����\n" NOR);
        } else
        {
                me->start_busy(3);
                me->add("neili", -60);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

