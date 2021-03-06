// shou.c 九阴破元手
// created by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define SHOU  "「" HIG "九阴破元手" NOR "」"
 
int perform(object me, object target)
{
	string msg;
        int ap, dp;
        
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail(SHOU "只能在战斗中对对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("此招只能空手施展！\n");

	if (me->query_skill("jiuyin-shengong", 1) < 220)
		return notify_fail("你的九阴神功还不够娴熟，不能使用" SHOU "！\n");

	if (me->query("neili") < 500)
		return notify_fail("你的真气不够！\n");

        if (me->query_skill_prepared("hand") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展" SHOU "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

       msg = HIY "$N" HIY "“哈”的一声吐出了一口气，手式奇特，软绵绵的奔向$n"
              HIY "的要穴！\n";

        ap = me->query_skill("jiuyin-shengong",1);
        dp = target->query_skill("parry",1);

       if (ap * 3 / 5 + random(ap) > dp) 
        { 
             msg +=  HIR "$n" HIR "只觉此招，阴柔无比，诡异莫测，"
                         "心中一惊，却猛然间觉得一股阴风透骨而过。\n" NOR;
			 target->start_busy(random(ap / 30) + 2);
       me->add("neili", -100);
       target->set("neili", target->query("neili") / 2);
			 me->start_busy(1);
		}
		else
		{
			msg += HIC "$n" HIC "知道来招不善，小心应对，没出一点差错。\n" NOR;
			me->add("neili", -50);
		    me->start_busy(2);
		}
 
		message_combatd(msg, me, target);
        return 1;
}
        
