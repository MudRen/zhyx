#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{               
        int skill;      
        if (me->query_temp("gang")) 
                return notify_fail(HIG "你已经在运混元天罡了。\n" NOR);
                
        if ((int)me->query("neili") < 400)
                return notify_fail("你的内力还不够！\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("你的混天气功的修为不够，不能使用混元天罡! \n");

		message_combatd(HIW "$N" HIW "使出混天气功绝学「混元天罡」，一股白气自顶心泥丸发散而下，全身弥漫在白色薄雾中！\n" NOR, me);             
        
        skill = me->query_skill("force");
		me->add_temp("apply/unarmed_damage", skill / 5);
        me->add("neili", -100);
		me->set_temp("gang", 1);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        if (me->is_fighting()) me->start_busy(2);
        return 1;
}

void remove_effect(object me, int skill)
{
        if ((int)me->query_temp("gang")) 
        {
                me->add_temp("apply/unarmed_damage", -(skill / 5));
                me->delete_temp("gang");
                tell_object(me, HIY "你的混元天罡运行完毕，将内力收回丹田。\n" NOR);
        }
}

