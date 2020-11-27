#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ��������ʮ�������������Լ���ս������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        message_combatd(HIR "$N" HIR "˫Ŀ΢�գ����ھ�����������������תʮ�����죬��"
                        "ʱֻ��һ�������ޱȵ���������ȫ��\n" NOR, me);

        if (!me->query("breakup"))
        {
		me->add_temp("apply/attack", skill / 3);
		me->add_temp("apply/defense", skill / 3);
		me->add_temp("apply/unarmed_damage", skill / 4);
		me->add_temp("apply/damage", skill / 4);
		me->add_temp("apply/parry", skill / 5);
		me->add_temp("apply/dodge", skill / 5);
		me->add_temp("apply/armor", skill * 2 / 3);
        }
        else
        {
        	me->add_temp("apply/attack", skill / 2);
	        me->add_temp("apply/defense", skill / 2);
        	me->add_temp("apply/unarmed_damage", skill / 3);
	        me->add_temp("apply/damage", skill / 3);
        	me->add_temp("apply/parry", skill / 3);
	        me->add_temp("apply/dodge", skill / 3);
        	me->add_temp("apply/armor", skill);
        }

        me->set_temp("powerup", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
             if (!me->query("breakup"))
             {
	        me->add_temp("apply/attack", - (amount / 3));
	        me->add_temp("apply/defense", - (amount / 3));
	        me->add_temp("apply/unarmed_damage", -(amount / 4));
	        me->add_temp("apply/damage", -(amount / 4));
	        me->add_temp("apply/parry", - (amount / 5));
	        me->add_temp("apply/dodge", - (amount / 5));
	        me->add_temp("apply/armor", - (amount * 2 / 3));
             }
             else
             {
	        me->add_temp("apply/attack", - (amount / 2));
	        me->add_temp("apply/defense", - (amount / 2));
	        me->add_temp("apply/unarmed_damage", -(amount / 3));
	        me->add_temp("apply/damage", -(amount / 3));
	        me->add_temp("apply/parry", - (amount / 3));
	        me->add_temp("apply/dodge", - (amount / 3));
	        me->add_temp("apply/armor", - amount);              
             }
                me->delete_temp("powerup");
                tell_object(me, HIW "�������ʮ������������ϣ��������ջص��\n" NOR);
        }
}
