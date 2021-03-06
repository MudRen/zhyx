#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

#define HUA "「" HIR "化妖功" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg, parry_str;
        int ap, dp, p;
        int lv, cost_neili;

        if (userp(me) && ! me->query("can_perform/zhemei-shou/hua"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUA "只能空手施展。\n");
                
        if (me->query("int") < 34)
                return notify_fail("你先天悟性不足，无法施展灵巧的终极绝招。\n");
                
        if ((int)me->query_skill("beiming-shengong", 1) < 250)
                return notify_fail("你的北冥神功火候不够，难以施展" HUA "。\n");

        if (lv = (int)me->query_skill("zhemei-shou", 1) < 250)
                return notify_fail("你逍遥折梅手等级不够，难以施展" HUA "。\n");

        if (me->query("max_neili") < 4500)
                return notify_fail("你的内力修为不足，难以施展" HUA "。\n");

        if (me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你没有激发北冥神功，难以施展" HUA "。\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("你没有激发逍遥折梅手，难以施展" HUA "。\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou")
                return notify_fail("你没有准备逍遥折梅手，难以施展" HUA "。\n");

        if (me->query("neili") < 500)
                return notify_fail("你现在真气不足，难以施展" HUA "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY"                       真   *   化       妖        功!!!!!!!!!!\n\n"HIM "$N" HIM "深深吸进一口气，将北冥神功运至极限,单手挥出，掌缘顿时霞光万道，漾出"
              "七色虹彩向$n" HIM "席卷而至。\n\n" NOR;

        ap = me->query_skill("zhemei-shou", 1) + me->query_skill("dodge", 1)+me->query_skill("beiming-shengong", 1);
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1)+target->query_skill("martial-cognize", 1);

        if (target->is_bad() || ! userp(target))
                ap += ap / 10;

        if (ap * 2 / 3 + random(ap) + random(20) > dp)
        {
                damage = 0;
                lv = me->query_skill("zhemei-shou", 1);
                if (lv >= 220)cost_neili = -250;
                if (lv >= 260)cost_neili = -220;
                if (lv >= 300)cost_neili = -190;
                if (lv >= 360)cost_neili = -160;
                
                if ( me->query("max_neili") > target->query("max_neili") * 2
                     && me->query("neili") > 500 )
                {
                        msg += HIM "只听$n" HIM "一声尖啸，$N" HIM "的七色掌"
                               "劲已尽数注入$p" HIM "体内，顿时将$p" HIM "化"
                               "为一滩血水。\n" NOR "( $n" RED "受伤过重，已"
                               "经有如风中残烛，随时都可能断气。" NOR ")\n";
                        damage = -1;
                        me->add("neili", cost_neili);
                       // me->start_busy(3);
                } else
                {
                        damage = ap;
                        damage += me->query_temp("apply/unarmed_damage");
                        damage += random(damage);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p = (int)target->query("qi") * 100 / (int)target->query("max_qi");

                        msg += HIM "$n" HIM "只是微微一愣，$N" HIM "的七色掌劲已破体而"
                               "入，$p" HIM "便犹如身置洪炉一般，连呕数口鲜血。\n\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        
                                     
                        
                      //  me->add("neili", cost_neili);
                      //  me->start_busy(3);
                }
        } else
        {
                msg += CYN "$p" CYN "见状大惊失色，完全勘破不透$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
              
        }
       
       msg +=HIY"$N连连崔动北冥神功,脸上寒光四射!突然五指连拂,连出三招，扫向$n\n\n"NOR;
       
       
        if (ap * 3 / 5 + random(ap) > dp)          
        {          
                    damage = ap + me->query_skill("beiming-shengong",1) * 2;
                    
	                me->add("neili", -150);
                    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIG "只听“扑哧”一声，$N" HIG "手掌击在$n" HIG "身上的要穴上，$n"
                                   HIG "一声惨叫，血射五步。\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "见状不慌不忙，看破了$N$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
               
        }
        
         if (ap * 2 / 3 + random(ap) > dp)          
              {          
                    damage = ap + me->query_skill("beiming-shengong",1);
                    
	                 me->add("neili", -100);
                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                   HIG "紧接着,$N双手虚空一按，只听“扑哧”一声，" HIG "$n" HIG "身上破了一个血洞"
                                   HIG "情状恐怖。\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "见状不慌不忙，看破了$N$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
              
        }
        
        
         if (ap * 3 / 4 + random(ap) > dp)          
              {          
                    damage = ap;
                    
	                   me->add("neili", -100);
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                   HIG "$N嘿嘿一声阴笑，双手虚摆胸前，作美人折梅妙曼姿态，双手回旋牵引，一股股气流笼罩着$n\n"
                                   HIG "$n受气机压迫，哇的一声，吐出一口鲜血。\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "见状不慌不忙，看破了$N$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
               
                
        }
       
        
        if (me->query("reborn"))
        	{
                   if (ap * 4 / 5 + random(ap) > dp)
        	
        	   {
                        parry_str = target->query_skill_mapped("parry");

                            damage = ap + me->query_skill("beiming-shengong",1) * 4;
                        if (me->query_skill("zhemei-shou", 1) > 799)
                        {
                            damage = damage * 2 + random(damage);
                            target->map_skill("parry", 0);
                        }
                    
	                   me->add("neili", -200);
        		    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 110,
        		                          HIY "\n$N是转世之人，使出折梅手转世绝招梅花三弄。\n\n"
        		                          HIY "$N口中轻吟:梅花舞清影，三弄合为一,将北冥神功运至极限,幻起层层手影,方圆百米内罡风如刀\n\n"
        		                          HIM "$n无力抵抗,身上现出道道血流,心神俱碎,永堕无间地狱。\n" NOR);
                            target->map_skill("parry", parry_str);

             } else
      	
      	           {
                msg += CYN "$p" CYN "见状不慌不忙，看破了$N$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
                me->add("neili", -100);
              
                    }
          }
           me->start_busy(3+random(4));
        message_combatd(msg, me, target);

        if (damage < 0)
        {      //  target->die(me);
            target->set("eff_qi", -1);
            target->set("eff_jing", -1);
        }
        return 1;
}
