// wannian.c 万念俱灰

#include <ansi.h>
#include <combat.h>

#define WANNIAN "「" HIM "万念俱灰" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, qi, maxqi;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/sad-strike/wannian")) 
                return notify_fail("你还没有学会「万念俱灰」这一招！\n");
        if (! target || ! me->is_fighting(target))
                return notify_fail(WANNIAN "只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你拿着兵器如何出黯然销魂掌法？\n");
        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("你的内功火候不够，使不出" WANNIAN "。\n");

        if (me->query_skill_mapped("strike") != "sad-strike" &&
            me->query_skill_mapped("unarmed") != "sad-strike" ||
            me->query_skill_prepared("unarmed") != "sad-strike" &&
            me->query_skill_prepared("strike") != "sad-strike")
        return notify_fail("你现在没有准备使用黯然销魂掌，无法使用 " WANNIAN "。\n");

        if ((int)me->query_skill("sad-strike", 1) < 250)
                return notify_fail("你的黯然销魂掌不够熟练，不会使用" WANNIAN "。\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("你的真气不够，无法使用" WANNIAN "。\n");

        msg = HIM "$N" HIM "心下万念俱灰，没精打采的挥袖卷出，拍出一掌，恍恍惚惚，\n"
              HIM"隐隐约约，若有若无，竟是" HIR "“黯然销魂掌”" HIM "精粹之所在！！！\n" NOR;

        qi = me->query("eff_qi");
        maxqi = me->query("max_qi");

        ap = me->query_skill("force") + me->query_str() * 2;
        dp = target->query_skill("dodge") + target->query_dex() * 2;

	if (qi < (maxqi * 0.4)) ap += ap/3;

        if(ap/2 + random(ap) > dp || !living(target))
	{
		if(qi > (maxqi * 0.4))
	        {
	                me->start_busy(3);
        		damage = ap * 2;
                        me->add("neili",-damage/2);
	                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
        	                HIR "$n" HIR "那里避得过了？砰的一响，正中胸口，鲜血狂喷！！！\n" NOR);
        	}
	        else 
		{
                	me->start_busy(3);
	                damage = ap * 2 + random(ap*2);
                        me->add("neili",-damage/2);
	        	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
        	                HIC "此刻生死关头，哀痛欲绝之际，" HIC "$N" HIC "的“黯然销魂掌”威力顿生！\n" HIR "$n" HIR "的胸口如遭千斤巨石撞击，剧痛无比！！！\n" NOR);
        	}
                target->start_busy(1);
	}
	else
        {
                msg += HIG "$n"HIG"冒死后退，$N"HIG"的掌风仅从胸口掠过，"
                       HIG "$n" HIG "顿时一阵窒息！\n" NOR;
                me->start_busy(2);
        }

        message_combatd(msg, me, target);

        return 1;
}
