// longhe.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;        

        if (target != me)
                return notify_fail("你只能用龙鹤庄提升自己的战斗力。\n");
		if ((int)me->query_skill("linji-zhuang", 1) < 90)
                return notify_fail("你的临济十二庄火候不够，难以施展龙鹤庄。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("longhe"))
                return notify_fail("你已经在运功中了。\n");
		if ((int)me->query_temp("fengyun"))
                return notify_fail("你正在运行风云庄中，不能运行龙鹤庄。\n");
		if ((int)me->query_temp("daxiao"))
                return notify_fail("你正在运行大小庄中，不能运行龙鹤庄。\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);        

        message_combatd(HIW "$N" +HIW "暗运龙鹤两庄，启天门，闭地户，聚精成力。\n" NOR, me);

      
        me->add_temp("apply/parry", skill / 3);       
        me->set_temp("longhe", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("longhe"))
        {               
                me->add_temp("apply/parry", -amount);              
                me->delete_temp("longhe");
                tell_object(me, "你的龙鹤庄运行完毕，将内力收回丹田。\n");
        }
}
