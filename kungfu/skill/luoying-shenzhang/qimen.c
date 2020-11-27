// qimen.c  ��Ӣ���ơ�������ת��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if(me->query_temp("weapon"))
                return notify_fail("��װ���ű�������ô���Ʒ���\n");
        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ת��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("luoying-shenzhang", 1) < 80)
                return notify_fail("�����Ӣ���Ʋ�����죬����ʹ�á�������ת����\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 100)
                return notify_fail("����������е��о�����͸�����޷����á�������ת����\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹��ߣ��޷�ʹ�á�������ת����\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�����������������޷�ʹ�á�������ת����\n");

        msg = HIG "$N" HIG "ͻȻ���Ī�⣬˫�Ʒ��ɣ�����ʵʵ�Ĺ���$n" HIG "��\n" NOR;

        ap = (int)me->query_skill("luoying-shenzhang", 1) +
             (int)me->query_skill("qimen-wuxing", 1) +
             (int)me->query_skill("force") +
             (int)me->query("int") * 10;

        dp = (int)target->query_skill("dodge") +
             (int)target->query_skill("parry") +
             (int)target->query_skill("qimen-wuxing", 1) +
             (int)target->query("int") * 10;

        me->start_busy(1);
        me->add("neili", -150);
        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(2 + random(3));

                damage = (int)me->query_skill("force") + (int)me->query_skill("strike");
                damage = damage / 4;
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "���һ��������ֵ����ˣ�"
                                           "������������ƣ�����һ����Ѫ�����Ӽ�"
                                           "ת����ͣ��\n" NOR);
        } else
                msg += HIG "����$p" HIG "������$P" HIG
                       "����ͼ���������򣬱ܿ���$P" HIG "��һ����\n"NOR;

        message_vision(msg, me, target);
        return 1;
}
