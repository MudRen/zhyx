#include <ansi.h>
#include <combat.h>

#define AOJUE "「" HIR "傲气中华" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        object weapon;
        string wn, msg;       
        int ap, dp, damage, lvl, idle, i, count;

        if (userp(me) && ! me->query("can_perform/china-aojue/aoqi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(AOJUE "只能对战斗中的对手使用。\n");

        if ( me->query("int") < 25 ) 
                return notify_fail("你的先天悟性不足，无法使用此招。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" AOJUE "。\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("你的内功修为不够，难以施展" AOJUE "。\n");

        if ((int)me->query("max_neili") < 6000)
                return notify_fail("你的内力修为不够，难以施展" AOJUE "。\n");

        if ((int)me->query_skill("china-aojue", 1) < 450)
                return notify_fail("你中华傲诀火候不够，难以施展" AOJUE "。\n");

        if ((int)me->query_skill("idle-force", 1) < 300)
                return notify_fail("你发呆神功等级不够，难以施展" AOJUE "。\n");

        if (me->query_skill_mapped("sword") != "china-aojue")
                return notify_fail("你没有激发中华傲诀为剑法，难以施展" AOJUE "。\n");

        if (me->query_skill_mapped("force") != "china-aojue")
                return notify_fail("你没有激发中华傲诀为内功，难以施展" AOJUE "。\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("你现在真气不够，难以施展" AOJUE "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();
        
        msg=HIG"$N" HIG"把" +wn+HIG"插地，双手负在背后，仰天而立，傲气逼人，正是“中华傲诀”最后一式:\n\n"
            HIR"                         “傲气中华”\n" NOR;

       message_combatd(msg, me, target);
                        
       msg = HIY "$N" HIY"一声吐纳，气贯双掌，左掌一抄，"+wn+HIY"竟被凌空扯起，\n"
                 "随即$N"HIY"右掌一拍，拍在"+wn+HIY"剑背之上，剑尖便向$n"HIY"胸口疾刺而去......\n"NOR;
       ap = me->query_skill("sword") + me->query_skill("force")+ me->query_skill("idle-force", 1) * 2;
       dp = target->query_skill("parry") + target->query_skill("dodge")+ target->query_skill("idle-force", 1) * 2;  
       
       if (ap * 4/ 5 + random(ap) > dp)
       	{
       		 damage = ap * 2 + random(ap);
             me->add("neili", -300);
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                        HIR "$n" HIR "措手不及，长剑已穿胸而过，鲜血洒满一地。\n" NOR);
        } else
        {
                me->add("neili", -100);                
                msg += CYN "$n" CYN"未及细想，急忙提气跃开。\n" NOR;
        }
        message_combatd(msg, me, target);
        
        msg=HIY"紧接着"+wn+HIY"飞回$N"HIY"手中，$N"HIY"以气御剑，意随心发，剑随气动，\n"
        HIY"$n"HIY"全身被笼罩在剑光之中......\n"NOR;
        message_combatd(msg, me, target);  
        
        count=ap/2;    

        me->add_temp("apply/attack", count);
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, i * 2 );
				 me->add("neili", -50);   
        }
        me->add_temp("apply/attack", -count);
        

        msg = HIR "\n突然$N" HIR "凝神沉履，神情呆滞，手中"+wn+HIR"飘忽不定地奔向$n。\n" NOR;
        
        ap = me->query_skill("force",1) + me->query_skill("idle-force", 1);
        dp = target->query_skill("force",1) + target->query_skill("idle-force",1);   
         
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 4 + random(ap*2);                
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "结果$n" HIR "招架不及，被$N" HIR
                                           "一剑刺在胸口，接连刺断了数根肋骨，喷出"
                                           "一大口鲜血！\n" NOR);           

        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
			    me->add("neili", -50);
        }
        message_vision(msg, me, target);
        me->start_busy(3 + random(4));
        
        return 1;
}


