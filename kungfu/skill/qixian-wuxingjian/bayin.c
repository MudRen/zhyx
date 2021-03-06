//by gentl
//说明：梅庄七弦无形剑之终极绝招，打精不打气，诸多特效，使用此招需悟性不小于40.

#include <ansi.h>
#include <combat.h>

#define BAYIN "「" HIW "七弦八音" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int ap, an, dn, dp, wp;
        int count;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }


        if (! me->is_fighting(target))
                return notify_fail(BAYIN "只能对战斗中的对手使用。\n");

        skill = me->query_skill("qixian-wuxingjian", 1);
		
        weapon = me->query_temp("weapon");		

        if (me->query_skill("force") < 1200)
                return notify_fail("你的内功的修为不够，现在无法使用" BAYIN "。\n");

        if (skill < 800)
                return notify_fail("你的七弦无形剑修为有限，现在无法使用" BAYIN "。\n");

        if ((int)me->query_skill("xuantian-wujigong", 1) < 500)
                return notify_fail("你的玄天无极功修为有限，现在无法使用" BAYIN "。\n");

        if (me->query("neili") < 2500)
                return notify_fail("你的真气不够，无法运用" BAYIN "。\n");
                
        if ( me->query("int") < 40 ) 
                return notify_fail("你的先天悟性不足，无法使用此招。\n");

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法领会此绝招！\n");                   

        if (weapon && weapon->query("skill_type") != "sword")
                return notify_fail("你不能使用这种兵器施展" BAYIN "。\n");

        if (weapon && me->query_skill_mapped("sword") != "qixian-wuxingjian")
                return notify_fail("你现在没有准备使用七弦无形剑，无法施展" BAYIN "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "qixian-wuxingjian")
                return notify_fail("你现在没有准备使用七弦无形剑，无法施展" BAYIN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if (weapon)
        {
                msg = HIW "只见$N" HIW "双目微闭，单手在" + weapon->name() +
                      HIW "上轻轻拨动，顿时只听“啵啵啵”破空之声连续不断"
                      "，数股破\n体无形剑气激射而出，直奔$n" HIW "而去，正是终极绝招之七弦八音。\n" NOR;
        } else
        {
                msg = HIW "只见$N" HIW "双目微闭，双手轻轻舞弄，陡然间十指一"
                      "并箕张，顿时只听“啵啵啵”破空之声连续不\n断，数股破"
                      "体无形剑气激射而出，直奔$n" HIW "而去，正是终极绝招之七弦八音。\n" NOR;
        }
        
        msg += MAG "            空中传来摄人心魄的旋律         \n"
               HIW " ～～～～～           七           ～～～～～ \n"
               HIC "    ～～～～～        弦        ～～～～～\n"
               HIG "       ～～～～～     八     ～～～～～\n"
               HIM "          ～～～～～  音  ～～～～～\n"  NOR;	

        ap = skill + me->query_skill("force", 1) + me->query_skill("unarmed", 1) + me->query_skill("sword", 1) + me->query_skill("tanqin-jifa", 1);
        an = me->query("max_neili") / 20 + me->query_skill("tanqin-jifa", 1);
        dn = target->query("max_neili") / 20 + target->query_skill("tanqin-jifa", 1);
        dp = target->query_skill("force", 1) + target->query_skill("dodge") + target->query_skill("parry");

        if (an / 2 + random(an) > dn)
        {
                msg += HIR "一阵阵金属铁器交鸣声响忽起，杀伐鼓舞战斗士气的音律，自" HIR "$N" HIR "手中流泄而出\n" NOR;
                count = ap / 5;                
                ap += ap / 4;
        }

        me->add("neili", -250);
        damage = ap * 3 / 2 + random(ap * 3/2);

//第一招
	    msg += HIW "\n$N" HIW "在琴上连弹数声，在琴音之中灌注上乘内力，用以扰乱敌人心神。\n" NOR;        
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只觉得$N" HIR "内力激荡，琴"
                       "音犹如一柄利剑穿透鼓膜，脑中一片混乱。\n";       	
                       
            target->receive_damage("jing", damage * 5 / 4, me);
            target->receive_wound("jing", damage, me);
            if (an / 3 + random(an) > dn && !userp(target))
            	{       
            		msg += HBWHT "只见" HBWHT "$n" HBWHT "内力和琴音一生共鸣，便不知不觉的为琴音所制。\n" NOR;
            		 target->start_busy(3 + random(ap / 100));  

            	}
        } else
        {
                msg += CYN "可是$n" CYN "急忙凝神聚气，努力使自己"
                       "不受琴音的干扰，终于化解了这一招。\n" NOR;
        }
        
        
//第二招        
	    msg += HIG "\n$N" HIG "十指渐快，琴声越弹越急，在内力鼓荡之下如剑气般向" HIG "$n" HIG "扑来。\n" NOR;        
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只觉得$N" HIR "内力激荡，琴"
                       "音犹如一柄利剑穿透鼓膜，脑中一片混乱。\n";        	
                       
            target->receive_damage("jing", damage * 4 / 3, me);
            target->receive_wound("jing", damage, me);
                if (objectp(weapon = target->query_temp("weapon"))
                   && weapon->query("stable", 1) < 100
                   && ap / 3 + random(ap) > dp && !userp(target))
                  {
                        wp = weapon->name();
                        msg += HBGRN "只听“锵”的一声脆响，$n" HBGRN "手"
                               "中的" + wp + HBGRN "在$N" HBGRN "内力激荡"
                               "下应声而碎，脱手跌落在地上。\n" NOR;
                        me->add("neili", -500);
                        weapon->set("consistence", 0);
                        weapon->move(environment(target));
                 }
        } else
        {
                msg += CYN "可是$n" CYN "急忙凝神聚气，努力使自己"
                       "不受琴音的干扰，终于化解了这一招。\n" NOR;
        }        
             
//第三招   
	    msg += HIM "\n时至最后，七弦同响，化成八道光束前后不一互相追逐如箭飞疾，直取" HIM "$n" HIM "而去。\n" NOR;        
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只觉得$N" HIR "内力激荡，琴"
                       "音犹如一柄利剑穿透鼓膜，脑中一片混乱。\n";    
                       
            target->receive_damage("jing", damage * 3 / 2, me);
            target->receive_wound("jing", damage, me);
            if (an / 3 + random(an) > dn && !userp(target))
            	{       
                 target->set("neili", 0);
                 msg += HBMAG "$n" HBMAG "心神受制，闷哼一声，倒退几步，顿觉内息涣散。\n" NOR;
                 
            	}
        } else
         {
                msg += CYN "可是$n" CYN "急忙凝神聚气，努力使自己"
                       "不受琴音的干扰，终于化解了这一招。\n" NOR;
         }   
                
        me->add("neili", -1000);
        me->start_busy(3 + random(4));
        message_combatd(msg, me, target);
        return 1;		 
        
        
}        
        
        
