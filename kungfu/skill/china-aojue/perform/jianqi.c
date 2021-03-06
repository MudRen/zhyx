#include <ansi.h>
#include <combat.h>

#define JIANQI "「" HIG "剑气长江" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;       
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/china-aojue/jianqi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIANQI "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" JIANQI "。\n");

        if ((int)me->query_skill("china-aojue", 1) < 350)
                return notify_fail("你的中华傲诀不够娴熟，难以施展" JIANQI "。\n");

        if (me->query("neili") < 800)
                return notify_fail("你现在真气不够，难以施展" JIANQI "。\n");

        if (me->query_skill_mapped("sword") != "china-aojue") 
                return notify_fail("你没有激发中华傲诀为剑法，难以施展" JIANQI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");       

        damage = me->query_skill("china-aojue", 1) + me->query_skill("martial-cognize", 1) + me->query_skill("sword", 1) + me->query_skill("idle-force", 1);
		damage = damage * 3 / 2 + random(damage);
        
        msg = HIW "$N"HIW"抖擞精神，气聚长剑之上，悍然刺出无数剑网，层层交叠，犹似长江大流，\n"
              HIW "滔滔不绝，如怒潮暴涌，迎上" HIW"$n。" HIW"正是中华傲决第三式："HIY"“剑气长江”\n\n"NOR;

        msg += HIG "$N" HIG "跨前一步，一剑直刺$n面门，毫"
              "无半点花巧可言。\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                   HIR "$n" HIR "奋力招架，怎奈功力有限，竟被刺个正着。\n" NOR);            
        
         msg += MAG "\n紧接着$N" MAG "力贯剑身，横扫$n小腹，招式"
              "沉重无比。\n" NOR; 
         msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                   HIR "$n" HIR "内力不济，顿时被$N"HIR"剑招震伤。\n" NOR);
                                   
        msg += HIC "\n随即又见$N" HIC "飞身一跃，一剑当空直刺$n下盘，招式"
              "精奇无比。\n" NOR; 
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   HIR "$n" HIR "轻功尚欠火候，一不留神已然中招。\n" NOR);
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        me->add("neili", -600);
        
       
                                   
         
       /*
        if (ap * 4 / 5 + random(ap) > dp)
        {
              damage = ap*2 + random(ap);
              target->receive_damage("qi", damage * 3 / 2, me);
              target->receive_wound("qi", damage, me);
              msg += HIR "$n" HIR "奋力招架，怎奈功力有限，竟被刺个正着。\n" NOR;
              str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";

        } else
        {
                msg += HIC "只见$n" HIC "奋力抵挡。硬生生将$N"
                           "这一招挡了回去。\n" NOR;
        }
        message_combatd(msg, me, target);

       //第二招，考验对手内功
        dp = target->query_skill("force", 1);     
        msg = MAG "紧接着$N" MAG "力贯剑身，横扫$n小腹，招式"
              "沉重无比。\n" NOR; 
       
        if (ap * 4 / 5 + random(ap) > dp)
        {       
                damage = ap * 2 + random(ap);
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "内力不济，顿时被$N剑招震伤。\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";
        } else
        {
                msg += HIC "好在$n" HIC "内力深厚，瞬间气运丹田，一股真力"
                       "将$N剑身震开数寸。\n" NOR;
        }
        message_combatd(msg, me, target);

       //第三招，考验对手轻功
        dp = target->query_skill("dodge", 1); 
    
        msg = HIC "随即又见$N" HIC "飞身一跃，一剑当空直刺$n下盘，招式"
              "精奇无比。\n" NOR; 

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 2 + random(ap);
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "轻功尚欠火候，一不留神已然中招。\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";
        } else
        {
                msg += HIC "可是$n" HIC "轻功不凡，看准$N落剑方位，"
                       "轻轻巧巧飘开数丈，躲了过去。\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(3 + random(4));  */

        return 1;
}

