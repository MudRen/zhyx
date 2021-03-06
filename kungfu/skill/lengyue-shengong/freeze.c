// freeze.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object met);

int exert(object me, object target)
{
	int ap;
        int dp;
        int damage;
	int skill;
        string msg;

        if (target == me || ! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

        if ((skill = me->query_skill("lengyue-shengong", 1)) < 150)
                return notify_fail("你的冷月神功火候不够，无法运用寒气。\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你的内力不够!");

	if (me->query_temp("hu/freeze"))
		return notify_fail("你已经在运用冷月寒气了！\n");

	if (!target || target == me)
	{
                message_vision(HIW "$N" HIW "默运冷月神功，一股寒气从体内散发而出"
                      HIW "，四周登时雪花飘飘。\n" NOR,me);
		me->set_temp("hu/freeze",1);
       	        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);
		return 1;		
	}

        msg = HIW "$N" HIW "默运冷月神功，一股寒气迎面扑向$n"
              HIW "，四周登时雪花飘飘。\n" NOR;

	ap = me->query_skill("force");
        dp = me->query_skill("force");

        me->start_busy(2);

        if (ap / 2 + random(ap) > random(dp))
        {
                damage = ap / 2 + random(ap / 2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", random(damage), me);
                if (target->query("neili") > damage)
                        target->add("neili", damage);
                else
                        target->set("neili", 0);

                msg += HIG "$n" HIG "忽然觉得一阵透骨寒意，霎时间"
                       "浑身的血液几乎都要凝固了。\n" NOR;
                target->start_busy(1);
        } else
                msg += HIY "$n" HIY "感到一阵寒意自心底泛起，连忙"
                       "运动抵抗，堪勘无事。\n" NOR;

        message_combatd(msg, me, target);

	me->set_temp("hu/freeze",1);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);

	return 1;
}

void remove_effect(object me)
{
	if (!me) return;
        if ((int)me->query_temp("hu/freeze"))
        {
                me->delete_temp("hu/freeze");
                tell_object(me, "你的冷月寒气运行完毕，将内力收回丹田。\n");
        }
}
