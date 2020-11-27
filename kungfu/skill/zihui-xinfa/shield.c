// shield.c �ϻ��ķ�֮������
//

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
                return notify_fail("��ֻ�����ϻ��ķ��������Լ��ķ�������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("zihui-xinfa",1) < 50)
                return notify_fail("����ϻ��ķ���Ϊ������\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "��ָ�۳ɱ�������ͼ�Σ������ϻ��ķ���"
                        "��ʱȫ���������ʣ�����Ʈ�\n" NOR, me);

        me->add_temp("apply/armor", skill);
	me->set_temp("shield", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
        	me->add_temp("apply/armor", -amount);
        	me->delete_temp("shield");
                tell_object(me, "����ϻ��ķ�������"
                            "�ϣ��������ջص��\n");
        }
}
