// zhongnan.c ����һָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����һָֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("zhongnan-zhi", 1) < 35)
                return notify_fail("�������ָ��������죬����ʹ������һָ��\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("����ڹ���Ϊ����������ʩչ����һָ��\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("�����������������޷�ʹ������һָ��\n");

	if (me->query_temp("weapon"))
		return notify_fail("�����Ҫ���ֲ��ܷ�������һָ��\n");

        msg = HIY "$N" HIY "һָ�̳�����ס�Ļζ�������$n"
              HIY "��ҪѨ��\n" NOR;

        if (random(me->query_skill("finger")) > target->query_skill("parry") / 2 || !living(target))
        {
                me->start_busy(2);
                damage = me->query_skill("finger");
                damage = 40 + damage / 4 + random(damage / 5);
                me->add("neili", -60);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "���$p" HIR "�м�ʧ�󣬱�$P" HIR
                                           "��һָ���˸����ţ���Ϣ��ʱһ�ͣ���Ѫ������\n" NOR);
        } else
        {
                me->start_busy(3);
                me->add("neili", -20);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
