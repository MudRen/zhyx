//Created by kasumi
#include <ansi.h>
#include <combat.h>

#define SHEN "「" HIM "五神朝元千剑势" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage,count,i;
        string msg, wn, wp,wp2,str,dodge_str;
        object weapon,weapon2;
        int ap, dp;
        me = this_player();


        if (! target) target = offensive_target(me);
		
				if(me->query_temp("no_daizong"))
                return notify_fail("你正在使用绝招岱宗如何！\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHEN "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" SHEN "。\n");

        if ((int)me->query_skill("zhenyue-jue", 1) < 500)
                return notify_fail("你镇岳决不够娴熟，难以施展" SHEN "。\n");

        if ((int)me->query_skill("wuyue-shenjian", 1) < 500)
                return notify_fail("你五岳神剑不够娴熟，难以施展" SHEN "。\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("你没有激发五岳神剑，难以施展" SHEN "。\n");

        if ((int)me->query("max_neili") < 5500)
                return notify_fail("你的内力修为不足，难以施展" SHEN "。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在的真气不够，难以施展" SHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();   
		dodge_str=target->query_skill_mapped("dodge");

		if (me->query_skill("zhenyue-jue", 1) > 500)
		{
			target->map_skill("dodge", 0);
		}

        
        msg = HIM "\n$N" HIM "微微一笑，内劲暴涨，手中" + wn + HIM "变幻万千，"
                  "『" HIR "祝融" HIM "』、『" HIY "紫盖" HIM "』、『" NOR WHT "石廪" HIM "』、『" HIG "芙蓉" HIM "』、『"
                  HIW "天柱" HIM "』五套剑法交替使出，电光火石间已袭向$n" HIM "全身......\n" NOR;
        message_sort(msg, me, target);
        
        ap = me->query_skill("wuyue-shenjian", 1);
        dp = target->query_skill("dodge", 1);

        if (me->query_skill("wuyue-shenjian", 1) > 799 && me->query("reborn"))
        {
                ap += ap / 5;
        }

        //祝融
        msg = HIY "\n$N" HIY "怒喝一声，将真气注入剑身，剑体顿时变得通红，一式「" HIR "万剑焚云" HIY "」使出，"
                  "霎时呼啸声大作，手中" + wn + HIY "化做千万柄利刃，笼罩$n" HIY "周身。" NOR; 
        message_sort(msg, me, target);
        
        if (ap * 3 / 4 + random(ap) > random(dp))
        {
                damage = ap*3 + random(ap*2);          
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                          (: final, me, target, damage :));         
         } else
         {
         	msg = CYN "$n" CYN "眼剑" +wn + CYN"已至，强自镇定，"
                      "侧身躲过，但对$N" CYN "这招仍是心有余悸。\n" NOR;       		
         }
         message_combatd(msg, me, target);   

        //芙蓉      
         
        msg = HIY "\n$N" HIY "轻啸一声，腾空而起，" + wn + HIY"在空中挽出一个剑"
              HIY "花，顷刻间剑花四散，洋洋洒洒。犹如无数芙蓉花瓣从半空洒向$n"
              HIY "全身。" NOR;
        message_sort(msg, me, target);

        if (ap * 3 / 4 + random(ap) > random(dp))
        {
         	damage = ap*3 + random(ap/2);    

         	msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "只见无数剑花袭来，将自己包围"
                                           "住，正犹豫间，$n" HIR "已被" + wn + HIR 
                                           "刺得皮开肉绽。\n" NOR);         	
        } else
        {
         	msg = CYN "然而$n" CYN "看出其中的破绽，侧身一跳"
                      "已然躲过$N" CYN "这一剑。\n" NOR;       		
        }
        message_combatd(msg, me, target);
      
         
         //紫盖
         msg = HIG "\n只见$N" HIG "一剑攻过并不收招，" HIG "竟而凌空回身反刺，" 
               HIG "确是一招「" HIC "紫盖回翔" HIG"」,手中" NOR + wn + HIG "直指$n" HIG "。" NOR;
         message_sort(msg, me, target);
         
         if (ap * 3 / 4 + random(ap) > dp)
         {
         	damage = ap * 2 + random(ap);
          target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage*4/5, me);
	        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	       	msg = "($n"+str+")\n";        	
        } else
        {
         	msg = CYN "然而$n" CYN "眼见" + wn + CYN "已至，但$n"
                      CYN "身法迅速无比，提气向后一纵，$N" CYN "扑了"
                      "个空。\n" NOR;
        }
        message_combatd(msg, me, target);
        
        //石廪
        msg = HIW "\n紧接着，$N" HIW "手腕轻轻一抖，一式「" HIG"落英纷飞" HIW"」手中"
                  + weapon->name() + HIW "化为漫天剑光，星星点点洒向$n" HIW "。\n" NOR;
        message_sort(msg, me, target);
        count=me->query_skill("sword") / 3;
        me->add_temp("apply/attack", count);        
        for (i = 0; i < 7; i++)
	      {
		        if (! me->is_fighting(target))
			           break;
			      if (! target->is_busy() && random(2) == 1)
                       target->start_busy(1);
	        COMBAT_D->do_attack(me, target, weapon, 0);
	      }
        me->add_temp("apply/attack", -count);        
        
        //天柱
        
        if (objectp(weapon2 = target->query_temp("weapon")))
        {
             wp2 = weapon2->name();
	           msg = MAG "$N" MAG "攻势微微一缓，突然施展出「烟云锁身剑」，手中" +
                      wn + MAG "幻作一道白芒，撩向$n" MAG "所持的" + wp2 + MAG "。\n" NOR;                		

	             if (random(me->query_skill("sword")) > target->query_skill("parry") / 2)
              	{
                	msg += HIR "$n" HIR "只见眼前白芒暴涨，登时右手一轻，"
                              + wp2 + HIR "竟脱手飞出。\n" NOR;
                	target->start_busy(3);
                  weapon2->move(environment(target));
        	      } else
		            {
        	      	msg += CYN "可是$n" CYN "看破$N" CYN "剑法中的虚招，镇"
                             "定自如，从容应对。\n" NOR;
        	      }
        	    message_sort(msg, me, target); 
	       }else
	       {
		          msg = MAG "$N" MAG "攻势微微一缓，突然施展出「" HIW "烟云锁身剑"
                    NOR MAG "」，手中" + wn + MAG "剑光夺目，欲将$n" MAG "笼罩在"
                      "剑光之中。" NOR;    
              ap = me->query_skill("sword");
              dp = target->query_skill("parry");    		
         
	             if (random(ap) > dp / 2)
               	{                	
                	msg += HIR "\n$n" HIR "惊慌不定，顿时乱了阵脚，竟被困于$N"
                               HIR "的剑光当中。\n" NOR;
                  target->start_busy(random(ap)/50 + 1);
              	
              	} else
		            {
        	     	msg += CYN "\n可是$n" CYN "看破$N" CYN "剑法中的虚招，镇"
                               "定自如，从容应对。\n" NOR;
        	      } 
        	      message_combatd(msg, me, target);       	      
	        }        
        target->map_skill("dodge", dodge_str);
        me->start_busy(3+random(4));
        me->add("neili", -1000);
       return 1;
        
}


string final(object me, object target, int damage)
{
        int lvl, n;

        lvl = me->query_skill("wuyue-shenjian", 1);
        n = 1 + random(lvl / 20);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id"       : me->query("id"),
                   "duration" : lvl / 20 + random(lvl / 20) ]));

        return  HIR "只见$N" HIR "这一招疾如电、猛如火，$n"HIR"心中惊疑不定，电光火石间，已被\n"
                HIR "$N"HIR"划中数剑，剑伤处嗤嗤作响，鲜血从外衣渗出。\n" NOR;
}
