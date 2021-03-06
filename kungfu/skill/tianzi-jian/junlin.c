//junlin.c 君临天下--天子剑终极绝招

#include <ansi.h>
#include <combat.h>

#define JUNLIN "「" HIY "君临天下" NOR "」"
inherit F_SSERVER;


string final2(object me, object target, int damage, int lvl);
string final3(object me, object target, int damage, int lvl);
string final5(object me, object target, int damage, int lvl);

int perform(object me, object target)
{
        int damage, i, count;
        string msg, sub_msg;
        int ap, dp;
        object weapon;       
        int lvl;

        if (userp(me) && ! me->query("can_perform/tianzi-jian/junlin"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUNLIN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" JUNLIN "。\n");   
        if (me->query_skill_mapped("sword") != "tianzi-jian")
                return notify_fail("你没有激发天子剑法，难以施展" JUNLIN "。\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你内力修为不够，难以施展" JUNLIN "。\n");

        lvl = (int)me->query_skill("tianzi-jian", 1);
        if (lvl < 300)
                return notify_fail("你天子剑法火候不够，难以施展" JUNLIN "。\n");

        if ( me->query("int") < 25 ) 
                return notify_fail("你的先天悟性不足，无法使用此招。\n");   

        if ((int)me->query("neili") < 1500)
                return notify_fail("你现在真气不够，难以施展" JUNLIN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");       

        message_sort(HIY "\n$N" HIY "乃是真命天子，盛怒之下皇者天威自然透出，"
                     "剑招更散发出无上神威，将「君临天下」的精髓发挥得淋漓尽致，"
                     "五式剑招源源不断地向$n" HIY"涌来！\n\n"NOR, me, target);

        weapon = me->query_temp("weapon");


        ap = me->query_skill("tianzi-jian", 1)  +              
             me->query_skill("martial-cognize", 1);
        damage = ap + random(ap);


       //第一式「龙跃九天破凌霄」
        msg = HIG "\n只见$N" HIG "施出「君临天下」第一式「龙跃九天破凌霄」，手中"
              + weapon->name() + HIG"犹如被囚于牢笼中的蛟龙终于脱困，张牙舞爪直飞九天"
              "之上。\n\n" NOR; 

        dp = target->query_skill("parry", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           HIR "$n" HIR "急忙飞身躲避，然而这一剑来得过快"
                                          "，只听$n" HIR "一声惨叫，这一剑已将$n" HIR "刺得"
                                          "鲜血飞溅。\n" NOR); 
 
        }
        message_sort(msg, me, target);

       //第二式「君临天下风云变」     
        msg = HIY "\n$N" HIY "施出「君临天下」第二式「君临天下风云变」"
              "，剑招冲破气劲，直刺向$n" HIY"左胸，所有劲力尽皆收敛，凝聚剑尖之上，"
              "劲力更为集中！\n\n" NOR;   
        dp = target->query_skill("dodge", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70 + random(5),
                                           (: final2, me, target, damage, lvl :));
        }
        message_sort(msg, me, target);

    
       //第三式「虎踞千山傲尘世」

        msg = HIW "\n$N" HIW "施出「君临天下」第三式「虎踞千山傲尘世」"
              "，剑势化成一头凶恶猛虎，怒扑而上，把$n" HIW"剑轮吞噬，更向$n" 
              HIW"扑去！\n\n" NOR;   
        dp = target->query_skill("force", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                          (: final3, me, target, damage, lvl :));

        }
        message_sort(msg, me, target);

       //第四式「龙颜一怒惊百里」

        msg = HIC "\n$N" HIC "施出「君临天下」第四式「龙颜一怒惊百里」"
              "，剑势化成一头凶恶猛虎，怒扑而上，似乎要将$n" HIC"整个人吞噬！\n\n" NOR;   

        dp = target->query_skill("literate", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           HIR "$n" HIR "急忙飞身躲避，然而这一剑来得过快"
                                          "，只听$n" HIR "一声惨叫，这一剑已将$n" HIR "刺得"
                                          "鲜血飞溅。\n" NOR); 
        }
        message_sort(msg, me, target);

       //第五式「气吞天下震乾坤」

        msg = HIR "\n$N" HIR "施出「君临天下」第五式「气吞天下震乾坤」，"
              "无数的森寒剑芒，疾卷成一个巨大的漩涡，天地间似乎燃起熊熊烈火，" 
              "漩涡之内更是带着炙热火劲，$n" HIR"被火劲侵入体内，焚身而殁！\n\n" NOR; 

       
        dp = target->query_skill("martial-cognize", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;	         
        } else
        {               
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           (: final5, me, target, damage, lvl :));

        }
        message_sort(msg, me, target);

        me->add("neili", - ( 1200 + random(300)) ); 
        me->start_busy(2 + random(3));
        return 1;
}

string final2(object me, object target, int damage,int lvl)
{
        target->add("neili", -(lvl + random(lvl)));

        return  HIR "$n" HIR "只觉$N" HIR "的天子霸气咄咄逼人，虽然奋力抵挡，怎奈$N的这"
                "招威力惊人，$n" HIR 
                "闷哼一声，丹田已被刺中，顿觉内息运行不畅，真力已然涣散！\n" NOR;
}

string final3(object me, object target, int damage, int lvl)
{       
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "眼见无数只猛虎向自己扑来，顿时心中一惊，"
                "只觉精力涣散，全身受制。\n" NOR;
}

string final5(object me, object target, int damage, int lvl)
{       
        target->start_busy(4 + random(lvl / 40));
        return  HIR "$n" HIR "遭受烈焰焚身之苦，一时间毫无还手之力，"
                "竟呆在原地动弹不得！\n" NOR;
}

