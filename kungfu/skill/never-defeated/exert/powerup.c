// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ò����������Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�����������!");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");

	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIY "$N" HIY "������Ц������������������"
                        "�½���Ȼ�����ƺ�Ҫ�˷��ȥ��ƮƮ���ɣ�\n" NOR, me);

	me->add_temp("apply/attack", skill * 2 / 5);
	me->add_temp("apply/defense", skill * 2 / 5);

	if (me->query("reborn"))
	{
		me->add_temp("apply/whip", skill / 6);
		me->add_temp("apply/club", skill / 6);
		me->add_temp("apply/sword", skill / 6);
		me->add_temp("apply/blade", skill / 6);
		me->add_temp("apply/staff", skill / 6);
		me->add_temp("apply/hammer", skill / 6);
		me->add_temp("apply/dragger", skill / 6);
		me->add_temp("apply/throwing", skill / 6);
                me->add_temp("apply/parry", skill / 6);
                me->add_temp("apply/dodge", skill / 6);
		me->add_temp("apply/damage", skill / 5);
	}

	me->set_temp("powerup", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
	        me->add_temp("apply/attack", -(amount * 2 / 5));
	        me->add_temp("apply/defense", -(amount * 2 / 5));
		if (me->query("reborn"))
		{
			me->add_temp("apply/whip", -(amount / 6));
			me->add_temp("apply/club", -(amount / 6));
			me->add_temp("apply/sword", -(amount / 6));
			me->add_temp("apply/blade", -(amount / 6));
			me->add_temp("apply/staff", -(amount / 6));
			me->add_temp("apply/hammer", -(amount / 6));
			me->add_temp("apply/dragger", -(amount / 6));
			me->add_temp("apply/throwing", -(amount / 6));
                        me->add_temp("apply/parry", -(amount / 6));
                        me->add_temp("apply/dodge", -(amount / 6));
			me->add_temp("apply/damage", -(amount / 5));
		}		
	        me->delete_temp("powerup");
                tell_object(me, "��Ĳ�����������ϣ��������ջص��\n");
        }
}
