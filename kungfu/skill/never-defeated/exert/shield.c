// shield.c ������
//

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ò������������Լ��ķ�������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("never-defeated",1) < 50)
		return notify_fail("��Ĳ�������Ϊ������\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force")/2;
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIC "$N" HIC "˫������һչ��һ�ɾ�����ʱ����ȫ��\n" NOR, me);

	if (me->query("reborn"))
		me->add_temp("apply/armor", skill);
	else
		me->add_temp("apply/armor", skill / 2);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
		if (me->query("reborn"))
			me->add_temp("apply/armor", -amount);
		else
			me->add_temp("apply/armor", -(amount/2));
        	me->delete_temp("shield");
        	tell_object(me, "��Ĳ�����������ϣ��������ջص��\n");
        }
}
