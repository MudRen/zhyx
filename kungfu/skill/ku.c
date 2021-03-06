#include <ansi.h>
#include <combat.h>

#define KU "「" HIW "苦海无涯回头是岸" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KU "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail(KU "只能空手使用。\n");

        if ((int)me->query_skill("force") < 800)
                return notify_fail("你内功修为不够，难以施展" KU "。\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("你内力修为不够，难以施展" KU "。\n");

        if ((int)me->query_skill("bluesea-force", 1) < 400)
                return notify_fail("你南海玄功火候不够，难以施展" KU "。\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("你没有激发南海玄功，难以施展" KU "。\n");

        if (me->query_skill_prepared("strike") != "bluesea-force")
                return notify_fail("你没有准备南海玄功，难以施展" KU "。\n");

        if ((int)me->query("neili") < 1500)
                return notify_fail("你现在真气不够，难以施展" KU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "凄然一声长啸，施出「" HIG "苦海无涯回头是岸"
              HIW "」，双掌翻滚出漫天掌影，尽数拍向$n" HIW "。\n" NOR;  

        ap = me->query_skill("strike") + me->query("str") * 100;
        dp = target->query_skill("force") + target->query("str") * 100;

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 400,
                                           HIR "$n" HIR "勘破不透掌中虚实，$N" HIR
                                           "双掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "连断了数根肋骨。\n" NOR);
	        message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "这掌来势非凡，不敢"
                       "轻易招架，当即飞身纵跃闪开。\n" NOR;
	        message_combatd(msg, me, target);
        }

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
        	COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add("neili", -500);
        me->start_busy(4 + random(3));
        return 1;
}

