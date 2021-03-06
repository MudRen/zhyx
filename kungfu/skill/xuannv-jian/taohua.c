#include <ansi.h>
#include <combat.h>

#define TAOHUA "「" HIR "人面桃花红" NOR "」"

inherit F_SSERVER;

string final1(object me, object target, int damage);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage);
string final4(object me, object target, int damage);
string final5(object me, object target, int damage);



int perform(object me, object target)
{
        object weapon;
        string wn, msg;       
        int ap, dp, damage, lvl;

        if (userp(me) && ! me->query("can_perform/xuannv-jian/taohua"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TAOHUA "只能对战斗中的对手使用。\n");

        if ( me->query("int") < 25 ) 
                return notify_fail("你的先天悟性不足，无法使用此招。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" TAOHUA "。\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("你的内功修为不够，难以施展" TAOHUA "。\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力修为不够，难以施展" TAOHUA "。\n");

        if ((int)me->query_skill("xuannv-jian", 1) < 300)
                return notify_fail("你玄女剑法火候不够，难以施展" TAOHUA "。\n");

        if (me->query_skill_mapped("sword") != "xuannv-jian")
                return notify_fail("你没有激发玄女剑法，难以施展" TAOHUA "。\n");

        if ((int)me->query("neili") < 600)
                return notify_fail("你现在真气不够，难以施展" TAOHUA "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        message_combatd(HIM "$N" HIM "微微一笑，轻挥手中" + wn +
                        HIM "，进而剑随音转，口中低吟道：\n" NOR, me, target);

       ap = me->query_skill("sword");
       damage = ap * 2 + random(ap);
       lvl = (int)me->query_skill("xuannv-jian", 1);


        // 第一招，比较对手招架

       dp = target->query_skill("parry");        

        message_vision(HIG "\n  去年今日此门中\n\n" NOR, me, target); 

        if (ap * 4/ 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final1, me, target, damage, weapon, lvl :));        

        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第二招，比较对手轻功

        dp = target->query_skill("dodge") ;        
        message_vision(HIM "\n    人面桃花相映红\n\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final2, me, target, damage, weapon, lvl :));              

        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第三招，比较对手内功
        dp = target->query_skill("force");  
      
        message_vision(HIY "\n      人面不知何处去\n\n" NOR, me, target); 
  
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final3, me, target, damage, weapon, lvl :));              

        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

	// 第四招，比较对手武学修养
        dp = target->query_skill("martial-cognize", 1);        
        message_vision(HIC "\n        桃花依旧笑春风\n\n" NOR, me, target);


        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10), (: final4, me, target, damage, weapon, lvl :));               
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第五招，比较对手读书写字？？天子也比较这个
        dp = target->query_skill("literate", 1);        
        message_vision(HIW "\n          神女生涯原是梦\n\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10), (: final5, me, target, damage, weapon, lvl :));               
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

        me->start_busy(3 + random(3));
        me->add("neili", -800 - random(200));
        return 1;
}

string final1(object me, object target, int damage)
{
        return HIR "$n" HIR "招架稍缓，已然中招，鲜血狂喷不止！\n" NOR;
}

string final2(object me, object target, int damage)
{
        return  HIR "$n" HIR "身法稍慢，已被$N剑招刺中，惨不堪言！\n" NOR;
}
string final3(object me, object target, int damage)
{
        return  HIR "$n" HIR "内功不济，顿时被$N真力震伤！\n" NOR;
}
string final4(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 6, me);
        target->receive_wound("jing", damage / 8, me);
        return  HIR "$n" HIR "窥不破$N招后有招，顿遭重创！\n" NOR;
}
string final5(object me, object target, int damage)
{
        target->start_busy(3 + random(3));
        return  HIR "$n" HIR "被$N身影所迷惑，目瞪口呆，动弹不得！\n" NOR;
}