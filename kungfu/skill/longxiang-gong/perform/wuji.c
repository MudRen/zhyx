#include <ansi.h>
#include <combat.h>

#define WUJI "「" HIW "般若无极" NOR "」"
inherit F_SSERVER;

int perform(object me, object target)
{
    object weapon;
    int ap, dp; 
    int i, count, shd, jia, layer, damage;
    string msg;
    

 
    if (! target) target = offensive_target(me);
    if (! target || ! me->is_fighting(target))
    		return notify_fail(WUJI "只能对战斗中的对手使用。\n");
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
    		return notify_fail(WUJI "只能空手施展。\n");
    if ((int)me->query_skill("longxiang-gong", 1) < 420)
    		return notify_fail("你的龙象般若功修为不够，难以施展" WUJI "。\n");
    if (me->query("max_neili") < 8500)
    		return notify_fail("你的内力修为不足，难以施展" WUJI "。\n");
    if (me->query_skill_mapped("unarmed") != "longxiang-gong")
    		return notify_fail("你没有激发龙象般若功为拳脚，难以施展" WUJI "。\n");
    if (me->query_skill_mapped("force") != "longxiang-gong")
    		return notify_fail("你没有激发龙象般若功为内功，难以施展" WUJI "。\n");
    if (me->query_skill_prepared("unarmed") != "longxiang-gong")
    		return notify_fail("你没有准备使用龙象般若功，难以施展" WUJI "。\n");
    if (me->query("neili") < 1000)
    		return notify_fail("你现在的真气不足，难以施展" WUJI "。\n");
    if (! living(target))
    		return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


    msg = HIY "$N" HIY "仰天一声怒嚎，将龙象般若功提运至极限，全身顿时罡劲"
        "迸发，真气蒸腾而出，笼罩$N" HIY "\n四方！电光火石间，$N" HIY "双"
        "拳已携着雷霆万钧之势崩击而出，卷起万里尘埃，正是密宗绝学：般若极！\n" NOR; 
    
        if ( me->query("max_neili") > target->query("max_neili") * 2 && me->query("neili") > 500 )
        {
        		msg += HIR "$n" HIR "全然无力阻挡，竟被$N"
        		HIR "一拳击得飞起，重重的跌落在地上。\n" NOR;
        		me->add("neili", -500);
        		me->start_busy(3);
        		message_combatd(msg, me, target);
      	    target->unconcious();
      	    return 1;
       } else
       {      
                ap = me->query_skill("unarmed") + me->query_skill("force") + me->query_str() * 10;
                dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
                if (ap + random(ap) > dp)
         	{
        	    if (target->query_temp("shield"))
        	    {
        	    		shd = target->query_temp("apply/armor");
        	    		target->add_temp("apply/armor", -shd);
        	    		target->delete_temp("shield");
        	  		msg += HIW "$N" HIW "罡气涌至，竟然激起层层气浪，顿时将$n"
        	  		   		HIW "的护体真气摧毁得荡然无存！\n" NOR;
        	    }
        	    jia = me->query("jiali");
                    damage = me->query_skill("longxiang-gong", 1) * 10 + random(jia * 10);
        	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
        	    	      HIR "$n" HIR "不及闪避，顿被$N" HIR
        	    	   	      "双拳击个正中，般若罡劲破体而入，尽"
        	    	   	      "伤三焦六脉。\n" NOR);
        	    me->add("neili", -400);
     	    } else
     	  	{
     	  	    me->add("neili", -200);
     	  	    msg += CYN "可是$n" CYN "识破了$N"
     	  	     	    CYN "这一招，斜斜一跃避开。\n" NOR;
     	  	}
			
			message_combatd(msg, me, target);

    msg = HIY "$N" HIY "仰天一声怒嚎，将龙象般若功提运至极限，全身顿时罡劲"
        "迸发，真气蒸腾而出，笼罩$N" HIY "\n四方！电光火石间，$N" HIY "双"
        "拳已携着雷霆万钧之势崩击而出，卷起万里尘埃，正是密宗绝学：般若极！\n" NOR;
 
    
        if ( me->query("max_neili") > target->query("max_neili") * 2 && me->query("neili") > 500 )
        {
        		msg += HIR "$n" HIR "全然无力阻挡，竟被$N"
        		HIR "一拳击得飞起，重重的跌落在地上。\n" NOR;
        		me->add("neili", -500);
        		me->start_busy(3);
        		message_combatd(msg, me, target);
      	    target->unconcious();
      	    return 1;
       } else
       {      
                ap = me->query_skill("unarmed") + me->query_skill("force") + me->query_con() * 10;
                dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
                if (ap + random(ap) > dp)
         	{
        	    if (target->query_temp("shield"))
        	    {
        	    		shd = target->query_temp("apply/armor");
        	    		target->add_temp("apply/armor", -shd);
        	    		target->delete_temp("shield");
        	  		msg += HIW "$N" HIW "罡气涌至，竟然激起层层气浪，顿时将$n"
        	  		   		HIW "的护体真气摧毁得荡然无存！\n" NOR;
        	    }
        	    jia = me->query("jiali");
                    damage = me->query_skill("longxiang-gong", 1) * 10 + random(jia * 10);
        	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
        	    	      HIR "$n" HIR "不及闪避，顿被$N" HIR
        	    	   	      "双拳击个正中，般若罡劲破体而入，尽"
        	    	   	      "伤三焦六脉。\n" NOR);
        	    me->add("neili", -400);
     	    } else
     	  	{
     	  	    me->add("neili", -200);
     	  	    msg += CYN "可是$n" CYN "识破了$N"
     	  	     	    CYN "这一招，斜斜一跃避开。\n" NOR;
     	  	}
			
			message_combatd(msg, me, target);
			
	    msg = HIY "$N" HIY "一道掌力打出，接着便涌出了第二道、第三道掌力，掌势"
        "连绵不绝，气势如虹！直到$N" HIY "\n第十三道掌力打完，四周所笼罩"
        "着的罡劲方才慢慢消退！而$n" HIY "此时却已是避无可避！\n" NOR;
			
                if (ap + random(ap) > dp)
     	  	{
     	 	      count = ap / 10;
     	 	 	    msg += HIR "$n" HIR "见$N" HIR "来势迅猛之极，一时不知该如"
     	 	 	    	    "何作出抵挡，竟呆立当场。\n" NOR;
     	 	 	} else
     	 	 	{
     	 	 	    msg += HIC "$n" HIC "见$N" HIC "来势迅猛之极，甚难防备，连"
     	 	 	    	    "忙振作精神，小心抵挡。\n" NOR;
     	 	 	    count = 0;
     	 		}
     	 			message_combatd(msg, me, target);
     	 			me->add_temp("apply/attack", count);
     	 			me->add("neili", -200);
     	 				for (i = 0; i < 8; i++)
     	 				{
     	 			    if (! me->is_fighting(target))
     	 			   		break;
     	 			    if (random(5) < 2 && ! target->is_busy())
     	 			    			target->start_busy(1);
     	 			    COMBAT_D->do_attack(me, target, 0, 0);
     	 			  }
     	 		me->start_busy(3 + random(3));
     	 		me->add_temp("apply/attack", -count);
     	  	return 1;
      }
}
}
