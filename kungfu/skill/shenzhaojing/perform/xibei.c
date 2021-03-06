#include <ansi.h>
#include <combat.h>

#define YING "「" HIR "无喜无悲" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, attack_time;
        string msg;
        int ap, dp;
        int i;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/shenzhaojing/ying"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (userp(me) && ! me->query("can_perform/shenzhaojing/wu"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能施展" YING "。\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("你没有激发神照经神功为空手技能，无法施展" YING "。\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("你现在没有准备使用神照经神功，无法施展" YING "。\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 300)
                return notify_fail("你的神照经神功火候不够，无法施展" YING "。\n");

        if ((int)me->query_skill("unarmed", 1) < 300)
                return notify_fail("你的基本拳脚火候不够，无法施展" YING "。\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("你的内力修为不足，无法施展" YING "。\n");

        if ((int)me->query("neili") < 1500)
                return notify_fail("你的真气不够，无法施展" YING "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_combatd(HIM "\n$N" HIM "默默念道：天地不仁以万物为邹狗！圣人不仁以百姓为邹狗！"
                     "逐渐沉入无喜无悲的无情境界。\n" NOR, me, target);

	damage = me->query_skill("shenzhaojing", 1) / 2 +
		 me->query_skill("martial-cognize", 1) +
		 me->query_temp("apply/unarmed_damage");

	damage = damage * (int)me->query_skill("zuoyou-hubo", 1) / 400;

	ap = me->query_skill("shenzhaojing",1) + me->query_skill("force") + me->query_skill("martial-cognize", 1) + me->query_skill("zuoyou-hubo", 1);
	dp = target->query_skill("dodge",1) + target->query_skill("force") + target->query_skill("martial-cognize", 1) + target->query_skill("zuoyou-hubo", 1) + target->query_skill("count", 1);

	if (me->query_skill("shenzhaojing",1)>899) me->set_skill("count", 300);

	attack_time = 1 + (int)(me->query_skill("zuoyou-hubo", 1) / 66);
	if (attack_time > 8) attack_time =8;

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
			break;

		message_combatd(HIW "$N" HIW "无声无影击出一拳，一股浑厚至极的内劲汹涌澎湃，" 
                     "带着排山倒海之势向$n" HIW "席卷而至。\n" NOR, me, target);

                if (ap * 4 / 5 + random(ap) > dp)
                {
			damage = damage + random(damage/5);
			msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 15,
				HIY "$n" HIY "思虑未定，$N" HIY "的内劲已破体而入，"
				"$n" HIY "受此重击，喉口一甜，呕出数口" HIR "鲜血" HIY "。\n" NOR);
                } else
                {
                        msg = CYN "$n" CYN "气凝双臂，奋力招架，将"
                              "$N" CYN "的内劲卸掉。\n" NOR;
                }

                message_combatd(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }
        me->start_busy(3+random(4));
        me->add("neili", -1000);

	if (me->query_skill("count",1)>0) me->delete_skill("count");

        return 1;
}
