#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIM "夺命连环三仙剑" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg,str;
        object weapon;
        int ap, dp, fp, pp;


        if (! target) target = offensive_target(me);
		
				if(me->query_temp("no_daizong"))
                return notify_fail("你正在使用绝招岱宗如何！\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对！\n");

        if ((int)me->query_skill("zixia-shengong", 1) < 300)
                return notify_fail("你紫霞神功不够娴熟，难以施展" XIAN "。\n");

        if ((int)me->query_skill("wuyue-shenjian", 1) < 300)
                return notify_fail("你五岳神剑不够娴熟，无法施展" XIAN "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你现在真气不够，无法施展" XIAN "！\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("你没有激发五岳神剑，无法使用" XIAN "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        me->add("neili", -600);

        ap = me->query_skill("wuyue-shenjian", 1) + me->query_skill("zixia-shengong", 1) + me->query_skill("sword", 1);
        dp = target->query_skill("dodge", 1) + target->query_skill("force");

        if (me->query_skill("wuyue-shenjian", 1) > 799 && me->query("reborn"))
        {
                ap += ap / 5;
        }

		if (me->query_skill("zixia-shengong", 1) > 400 && me->query_skill_mapped("force") == "zixia-shengong"){
		
			message_sort(HIW "\n$N" HIW "脸上紫气大盛，手中" + weapon->name() + HIW "随即不停转动，汹涌而"
                        "出，正是五岳神剑绝技「" HIM "夺命连环三仙剑" HIW "」，但见" + weapon->name() + HIW 
                        "剑锋突变，一剑顿时化为三剑，袭向$n" HIW "……\n" NOR, me, target);        

			msg = HIM "$N" HIM "将紫霞内功全力运至剑上，呼的一剑，当头直劈。\n" NOR;
			if (ap * 2 / 3 + random(ap) > dp)
			{
              damage = ap*2 + random(ap);
              target->receive_damage("qi", damage, me);
              target->receive_wound("qi", damage/2, me);
              msg +=  HIR "$n" HIR "急忙后退，竟然躲避不及，被$N"HIR "这一剑震得口吐鲜血，接连后退。\n" NOR;
              str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";

			} else
			{
                msg += CYN "$n" CYN "斜身闪开。\n" NOR;
			}
			message_combatd(msg, me, target);

  
			msg = HIM "\n$N" HIM "圈转" + weapon->name() + HIM "，拦腰横削，剑势恢弘，剑气纵横，令人匪夷所思。\n" NOR;
       
			if (ap * 2 / 3 + random(ap) > dp)
			{       
                damage = ap * 2 + random(ap*2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                msg += HIR "此招来势当真快及，$n" HIR "哪里来得及闪"
							"避招架？只见$N" HIR "剑光闪过，$n"HIR "腰间霎时鲜血淋漓！\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	msg += "($n"+str+")\n";
			} else
			{
              msg += CYN "$n" CYN "纵身从剑上越过。\n" NOR;
			}
			message_combatd(msg, me, target);
    
			msg = HIM "\n$N" HIM "长剑反撩，疾刺$p" HIM "后心，剑法之快，部位之准，当真闻所未闻。\n" NOR;

			if (ap * 3 / 4 + random(ap) > dp)
			{
                damage = ap * 3 + random(ap*2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage, me);
                msg +=  HIR "$n" HIR "身在空中，哪里来得及变招？只见$N"
                                 HIR "此剑掠过，$n" HIR "大声惨呼，鲜血四下飞溅！\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
				msg += "($n"+str+")\n";
			} else
			{
                msg += CYN "$n" CYN "身在空中，不及变招，只能挥出一招，正击中$N"
                       CYN "剑上，略一借力，飘然避去。\n" NOR;
			}
			message_combatd(msg, me, target);
			me->start_busy(3+random(2));
		}else{
		
			message_sort(HIW "\n$N" HIW "长啸一声，手中" + weapon->name() + HIW "随即不停转动，汹涌而"
                        "出，正是五岳神剑绝技「" HIM "夺命连环三仙剑" HIW "」，但见" + weapon->name() + HIW 
                        "剑锋突变，一剑顿时化为三剑，袭向$n" HIW "……\n" NOR, me, target);        

			msg = HIM "$N" HIM "将内力全都运到了剑上，呼的一剑，当头直劈。\n" NOR;

                damage = ap*2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(10),
                                           HIR "$n" HIR "急忙后退，竟然躲避不及，被$N"
                                           HIR "这一剑震得口吐鲜血，接连后退。\n" NOR);
        

			msg += HIM "\n$N" HIM "圈转" + weapon->name() + HIM "，拦腰横削，剑势恢弘，剑气纵横，令人匪夷所思。\n" NOR;

                damage = ap*2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(20),
                                           HIR "此招来势当真快及，$n" HIR "哪里来得及闪"
                                           "避招架？只见$N" HIR "剑光闪过，$n"
                                           HIR "腰间霎时鲜血淋漓！\n" NOR);
        

			msg += HIM "\n$N" HIM "长剑反撩，疾刺$p" HIM "后心，剑法之快，部位之准，当真闻所未闻。\n" NOR;

                damage = ap*2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(30),
                                           HIR "$n" HIR "身在空中，哪里来得及变招？只见$N"
                                           HIR "此剑掠过，$n" HIR "大声惨呼，鲜血四下飞溅！\n" NOR);
        

			me->start_busy(3);
			message_combatd(msg, me, target);
		}
        return 1;
}
