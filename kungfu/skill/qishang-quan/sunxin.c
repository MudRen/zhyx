// sunxin.c 损心诀

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

private void remove_effect(object me, int amount);

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, attack_decrease;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("「损心诀」只能在战斗中使用。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("cuff") < 60 )
                return notify_fail("你的拳法还不到家，无法体现七伤拳的各种总诀！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 60)
                return notify_fail("你七伤拳的修为不够，不能够体会损心诀! \n");

       if( (int)me->query_skill("force", 1) < 60)
                  return notify_fail(HIM "你的基本内功修为不足，不能随便使用损心诀! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你没有激发七伤拳，无法运用损心诀！\n");
        if (me->query_skill_prepared("cuff") != "qishang-quan")  
                return notify_fail("你没有准备使用七伤拳，无法施展「损心诀」。\n");  
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用此招！\n");


        msg = HIY "$N凝神定气，使出七伤拳总诀中的「" HIR "损心诀" HIY "」，双拳势如雷霆，向$n击去。\n"NOR;
        message_vision(msg, me, target);

        ap = me->query("combat_exp") + skill * 500;
        dp = target->query("combat_exp") / 2;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp || !living(target))
        {
                if(userp(me))
                        me->add("neili",-100);
                msg = HIG "$N连环拳势如风雷，$n中了$N开山裂石的一拳，顿时心神大震，不能随意出招！\n"NOR;
                attack_decrease = (int)target->query("apply/attack") / 10;
                target->add_temp("apply/attack", -attack_decrease);
                target->start_busy(2);
                me->start_busy(2 + random(2));
                call_out("remove_effect", skill/40, target, attack_decrease);
        }
        else
        {
                msg = HIG "只见$n不慌不忙，轻轻一闪，躲过了$N的必杀一击！\n"NOR;
                if(userp(me))
                        me->add("neili",-100);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

private void remove_effect(object me, int amount)
{
        if (!me)
                return;
        me->add_temp("apply/attack", amount);
        tell_object(me, "你感觉呼吸变得顺畅，所中的七伤拳损心劲气逐渐消解了。\n");
}
