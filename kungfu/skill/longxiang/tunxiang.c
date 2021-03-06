 //tunxiang.c   吞象式
//   looo/2001/6/21
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int bs;
        int damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(" 吞象式只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
            return notify_fail("你必须空手才能使用吞象式\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的内功的修为不够,不敢贸然使用吞象式。\n");

        if( (int)me->query_skill("lamaism",1) < 200 )
                return notify_fail("你的密宗心法不够，贸然使用吞象式恐怕会走火入魔\n");

        if (me->query_skill("longxiang", 1) < 250)
                return notify_fail("你的龙象般若功不够娴熟，不敢贸然使用吞象式。\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("你的内力不够，不敢贸然使用吞象式。\n");

        if( (int)me->query("neili", 1) < 1000 )
                 return notify_fail("你没有内力了！使用吞象式来找死吗？\n");

        if (me->query_skill_mapped("force") != "longxiang")
                return notify_fail("你没有激发龙象般若功，不敢贸然使用吞象式。\n");

        msg = HIY "$N" HIY "暴喝一声，巨臂一震，赫然动用了龙象般若功至高杀着--吞象式！\n"
              HIY "\n\n只见" HIY "$N" HIY "双臂顿时粗了一圈," HIY "$n" HIY "连同身前方圆三丈全在「龙象般若功」劲力笼罩之下！！\n"NOR;

        ap = me->query_skill("longxiang") + me->query("str") * 10;


 if (random(me->query_skill("force")) > target->query_skill("force")/2 || !living(target))
        {
                damage = ap + random(ap)*3/2;
                damage += me->query("jiali");
                bs = 4;
                me->add("neili", -800);
                me->add("neili",-me->query("jiali"));
                me->start_busy(bs);


         msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 150,
             HIR "数不清的拳影掌影象从四方八面压下来，" HIR "$n" HIR "觉得一口真气无法后继，连吐几口鲜血！！\n"NOR);
        } else

        {
           target->add("neili", -200);
                me->add("neili", -600);
           target->start_busy(2);
                me->start_busy(5);
                msg +=HIW "$n" HIW  "狠下决心，竟以全身内力相抗，两股真气碰撞一声，" HIW "$n" HIW "吐了一口鲜血，终于\n跳了出来，站也站不稳！！\n"NOR;
        }
                message_combatd(msg, me, target);

                return 1;
}


