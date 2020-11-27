// powerup.c ��󡹦����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ø�󡹦�������Լ���ս������\n");

	if ((int)me->query("neili") < 100 )
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");
		
	if ((int)me->query_temp("hmg_dzjm"))
		return notify_fail("����ת�����У��޷������˹�����ս����\n");

	skill = me->query_skill("force");
	me->add("neili", -100);

	message_combatd(HIR "$N" HIR "΢һ���������󡹦��ȫ"
                        "��ǽڷ���һ�󱬶�������죡\n" NOR, me);

	me->add_temp("apply/attack", skill / 2);
	me->set_temp("powerup", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
	        me->add_temp("apply/attack", -amount/2);
	        me->delete_temp("powerup");
	        tell_object(me, "��ĸ�󡹦������ϣ��������ջص��\n");
        }
}
