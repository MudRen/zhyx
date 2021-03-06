// throw.c 抽髓掌施毒
// By Yzuo 97.04

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object obj;
        string msg,str;
        int lvl, dp;

        if (! target) target = offensive_target(me);

        if (environment(me)->query("no_fight"))
                return notify_fail("这里不能攻击别人! \n");

        if (! target || ! target->is_character())
                return notify_fail("施毒只能对对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("你只有空手才能使用抽髓掌。\n");

        if (!(me->query_skill_mapped("strike") == "chousui-zhang"))
                return notify_fail("你并没有激发抽髓掌，如何用腐尸毒？\n");

        if (!(me->query_skill_prepared("strike") == "chousui-zhang"))
                return notify_fail("你并没有准备抽髓掌，如何用腐尸毒？\n");


        if (target->query("not_living"))
                return notify_fail("看清楚，那不是活人。\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 40)
                return notify_fail("你的化功大法不够娴熟，不能施毒。\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 40)
                return notify_fail("你的抽髓掌不够娴熟，不能施毒。\n");

        if (! (objectp(obj=present("corpse", environment(me)))  ||
            objectp(obj = present("corpse", me)) ||
            objectp(obj = present("Skeleton", environment(me))) ||
            objectp(obj = present("Skeleton", me)) ) )
                return notify_fail("你周围没有尸体，无法施展绝技。\n");

        msg = CYN "$N" CYN " 顺手抓起尸体，将毒质运于其上，掷向$n"
              CYN "。\n" NOR;

        if (living(target))
                dp = target->query_skill("dodge") / 2;
        else    dp = 0;

        if (random(lvl = (int)me->query_skill("chousui-zhang", 1)) > dp)
        {
                msg += HIR " 结果$p" HIR "被$P" HIR "攻了个正着！\n" NOR;
                target->receive_damage("qi",(int)me->query_skill("chousui-zhang", 1),me);
                target->receive_wound("qi",15 + random(10),me);
                target->receive_wound("jing", 10,me);
                target->affect_by("xx_poison",
                        ([ "level" : me->query_skill("poison",1),
                           "id"    : me->query("id"),
                           "duration" : me->query("poison",1)/20 ]));
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                msg += "($n"+str+")\n";
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "急忙闪在一旁，躲了开去。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        destruct(obj);
        return 1;
}

