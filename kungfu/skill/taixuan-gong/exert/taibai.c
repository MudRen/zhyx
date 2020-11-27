#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int count;

	if (! me->query("reborn"))
		return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

        if (userp(me) && (! me->query("can_perform/taixuan-gong/jing")||
		! me->query("can_perform/taixuan-gong/xuan")||
		! me->query("can_perform/taixuan-gong/hun")||
		! me->query("can_perform/taixuan-gong/po")))
		return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

	if (target != me)
		return notify_fail("��ֻ����̫�����������Լ���ս������\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("taibai"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	me->add("neili", -1000);

	me->receive_damage("qi", 500);

	message_combatd(HIM "$N" HIM "����̫���񹦣�Ĭ�" HIW "̫����ʫ" HIM "���ھ����پ�"
                        "�Լ������ޱȡ�\n" NOR, me);

	count = me->query_skill("taixuan-gong", 1);
	me->add_temp("apply/force", count / 6);
	me->add_temp("str", count / 10);
	me->add_temp("dex", count / 20);
	me->set_temp("taibai", 1);
	me->start_call_out((: call_other, __FILE__, "remove_effect", me, count :), count / 2);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int count)
{
        if ((int)me->query_temp("taibai"))
        {
		me->add_temp("apply/force", - count / 6);
		me->add_temp("str", - count / 10);
		me->add_temp("dex", - count / 20);
		me->delete_temp("taibai");
		tell_object(me, "��ġ�" HIW "̫����ʫ" NOR "��������ϣ��������ջص��\n");
        }

}

