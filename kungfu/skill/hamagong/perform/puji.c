// puji.c 蛤蟆扑击
// wrote by kasumi 2007.7
#include <ansi.h>

inherit F_SSERVER;

#define PUJI "「" HIG "蛤蟆扑击" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
       // if (userp(me) && ! me->query("can_perform/hamagong/puji"))
         //       return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(PUJI "只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(PUJI "只能空手使用。\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("hamagong", 1) < 200)
                return notify_fail("你的蛤蟆功火候不够，无法施展" PUJI "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，无法施展" PUJI "。\n");

        if (me->query_skill_prepared("unarmed") != "hamagong")
                return notify_fail("你现在没有准备使用蛤蟆功，无法施展" PUJI "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = MAG "$N双腿一弯，蹲下身来，“阁”的一声大叫，运起蛤蟆功劲力，双掌齐发，\n"
              MAG "掌力如山洪海啸般袭向$n。\n" NOR;      
        

        ap = me->query_skill("unarmed");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 4;
                msg += HIY "$n" HIY "见$P" HIY "这一招来势凶猛，怪异无"
                       "方，不由大吃一惊，慌乱中破绽迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "不敢小觑$P" HIC
                       "的来招，腾挪躲闪，小心招架。\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -300);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2)==0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(4));
        me->add_temp("apply/attack", -count);

        return 1;
}

