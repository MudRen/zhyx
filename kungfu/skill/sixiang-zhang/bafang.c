//bafang.c  ������ �˷�Ǭ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���˷�Ǭ����ֻ����ս���жԶ���ʹ�á�\n");

        if ((int)me->query("max_neili") < 600)
                return notify_fail("��������������ߣ�\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("��û�����ˣ�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ�����Ϊ����������ʹ�ð˷�Ǭ��!\n");

        if ((int)me->query_skill("sixiang-zhang", 1) < 120)
                return notify_fail("��������Ƶ���ϰ�������޷�ʹ�ð˷�Ǭ����\n");

        if (me->query_skill_mapped("strike") != "sixiang-zhang")
                return notify_fail("��û�м��������ƣ��޷�ʹ�ð˷�Ǭ����\n");

        msg = HIY "$N" HIY "��������ƾ�����������ǰ�����ƶ�������ס�����й����ķ�λ\n"NOR;
        ap = me->query_skill("sixiang-zhang");
        dp = target->query_skill("dodge");
if (random(me->query_skill("sixiang-zhang")) > target->query_skill("parry") / 3 || !living(target))
        {
                damage  = (int)me->query_skill("sixiang-zhang", 1);
                damage  = damage + (int)me->query_skill("strike", 1);
                damage  = damage + 200;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "ֻ��$N" HIR "��̤�������Բ���˫�����������һ��һ��"
                                           HIR "���Ʋ�ס$p����\n�ƣ�����ȴ�Ӳ����ܵĽǶ�����$p�ؿ�!!"
                                           HIR "$p��ʱһ�����\n" NOR);
                me->add("neili", -100);
                me->start_busy(2);
         } else
         {
                msg += CYN "����$p" CYN "�͵����һԾ��������$P"
                       CYN "�Ĺ�����Χ��\n" NOR;
                me->start_busy(3);
         }
         message_combatd(msg, me, target);
         return 1;
}
