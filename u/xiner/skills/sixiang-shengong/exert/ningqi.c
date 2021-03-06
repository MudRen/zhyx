#include <ansi.h>

inherit F_CLEAN_UP;

void qi_jing(object me);

int exert(object me, object target)
{
        object throwing;

        if (target != me)
                return notify_fail("凝气成团只能对自己使用。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够。\n");

        me->add("neili", -50);

	if (objectp(throwing = me->query_temp("handing")) && (string)throwing->query("id") != "qi jing")
		return notify_fail("你手上拿着东西如何凝气？\n");

	if (objectp(throwing = me->query_temp("handing")) && (string)throwing->query("id") == "qi jing" && throwing->query_amount() > 250)
		return notify_fail("你身上的气劲已经太多了！\n");


        message_combatd(HIW "$N" HIW "双手一合，掌间生出一点闪烁不定的"
                        "光芒，宛若一束无形气团，随身游走。\n" NOR, me);

        throwing = new("/clone/weapon/qijing.c");
        throwing->move(me);
	me->set_temp("handing", present("qi jing", me));
//        me->start_call_out((: call_other, __FILE__, "qi_jing", me :), 60);
         
        if (me->is_fighting())
                me->start_busy(2);

        return 1;
}

void qi_jing(object me)
{
        object throwing;
	throwing = me->query_temp("handing");
        if (objectp(throwing = me->query_temp("handing"))
           && (string)throwing->query("skill_type") == "throwing"
           && (string)throwing->query("id") == "qi jing")
       {
                if (me->is_fighting())
                        me->start_call_out((: call_other, __FILE__, "qi_jing",
                                              me :), 10);
                else
                        {
        message_combatd(HIG "$N" HIG "双手一合，掌间无形气劲，消逝不见。\n" NOR, me);
			destruct(throwing);
			}
        }
}