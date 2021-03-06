// zhua.c 九阴寂灭爪
// created by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHUA "「" HIR "九阴寂灭爪" NOR "」"

int perform(object me, object target)
{
    int damage;
    string msg;
    int ap, dp;

    if (!target)
        target = offensive_target(me);

    if (!target || !me->is_fighting(target))
        return notify_fail(ZHUA "只能对战斗中的对手使用。\n");

    if (me->query_temp("weapon"))
        return notify_fail(ZHUA "只能空手施展！\n");

    if ((int)me->query_skill("jiuyin-shengong", 1) < 250)
        return notify_fail("你的九阴神功还不够娴熟，不能使用" ZHUA "。\n");

    if ((int)me->query("neili", 1) < 300)
        return notify_fail("你现在内力太弱，不能使用" ZHUA "。\n");

    if (me->query_skill_prepared("claw") != "jiuyin-shengong" && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
        return notify_fail("你没有准备使用九阴神功，无法施展" ZHUA "。\n");

    if (!living(target))
        return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

    msg = HIY "$N" HIY "微微一笑，右手成爪，忽的抓向$n" HIY "的要穴！\n" NOR;

    ap = me->query_skill("jiuyin-shengong", 1) * 3 / 2 + me->query_skill("martial-cognize", 1);
    dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

    if (ap * 2 / 3 + random(ap) > dp)
    {
        damage = ap * 5 + random(ap * 2);
        me->add("neili", -200);
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                   HIR "只听“扑哧”一声，$N" HIR "五指正插入$n" HIR "的要害，$n" HIR "一声惨叫，血射五步。\n" NOR);
    }
    else
    {
        me->add("neili", -200);
        me->start_busy(3);
        msg += HIC "$n" HIC "暗叫不好，急忙闪头，可是$N" HIC "手臂咔咔作响，忽然暴长，迅论无比的抓向$n。\n" NOR;
        dp = target->query_skill("dodge") + target->query_skill("martial-cognize", 1);
        if (ap * 2 / 3 + random(ap) > dp)
        {
            damage = ap * 3 + random(ap / 2);
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                       HIR "$n" HIR "哪里料到$N" HIR
                                           "竟有如此变招，不及躲闪，肩头被$P" HIR "抓了个鲜血淋漓。\n" NOR);
        }
        else
            msg += CYN "$n" CYN "不及多想，急切间飘然而退，让$N" CYN "这一招无功而返。\n" NOR;
    }
    message_combatd(msg, me, target);

    return 1;
}
