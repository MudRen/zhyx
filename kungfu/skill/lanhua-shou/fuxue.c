// fuxue.c ������Ѩ�� ��������Ѩ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������Ѩֻ�ܶ�ս���ж���ʹ�á�\n");

        if(me->query_temp("weapon"))
                return notify_fail("ֻ�п��ֲſ���ʹ��������Ѩ�֡�\n");
	if ((int)me->query_dex() < 25)
		return notify_fail("��������������ʹ����һ������\n");

	if ((int)me->query_skill("force") < 140)
		return notify_fail("��̲��񹦵Ĺ�����������ʹ��������Ѩ��\n");

	if ((int)me->query_skill("hand") < 140)
		return notify_fail("����ַ���Ϊ������Ŀǰ������ʹ����"
				   "����Ѩ������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("���������ڲ���, ����ʹ���黨��Ѩ��\n");

	if (target->is_busy())
		return notify_fail(target->name() +
			           "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	msg = HIB "$N" HIB "���ַ������������ָͷ��ת��һ��ʢ����"
	      "��������ӯ������$n" HIB "��в��ҪѨ, ʹ$n" HIB "�������á�\n";

	if (random(me->query("combat_exp")) >
            target->query("combat_exp") / 3 || !living(target))
	{
		msg +=  HIB "���$p" HIB "��$P" HIB "������ţ���ʱ����"
		        "�޴룬�������أ�\n" NOR;
		target->start_busy((int)me->query_skill("lanhua-shou",1) / 19 + 2);
		me->add("neili", -100);
	} else
	{
		msg += HIY "����$p" HIY "������$P" HIY
		       "����ͼ������һԾ�����˿�ȥ��\n" NOR;
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
