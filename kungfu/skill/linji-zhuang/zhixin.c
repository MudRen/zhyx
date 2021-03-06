// zhixin.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;        

        if (target != me)
                return notify_fail("你只能用之心庄提升自己的防御力。\n");

		if ((int)me->query_skill("linji-zhuang", 1) < 60)
                return notify_fail("你的临济十二庄火候不够，难以施展之心庄。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("zhixin"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);        

        message_combatd(HIR "$N" +HIR "微一凝神，运动之心两庄，全身顿时笼罩在劲气之中！\n" NOR, me);

      
        me->add_temp("apply/armor", skill / 2);      
        me->set_temp("zhixin", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 2 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("zhixin"))
        {               
                me->add_temp("apply/armor", -amount);              
                me->delete_temp("zhixin");
                tell_object(me, "你的之心庄运行完毕，将内力收回丹田。\n");
        }
}
