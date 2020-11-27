// bei.c ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if ((int)me->query_skill("mingwang-jian", 1) < 90)
		return notify_fail("��Ĳ���������������죬����ʹ�á���������\n");

        if (me->query("neili") < 100)
                return notify_fail("�����������������޷�ʹ�á���������\n");

        if (me->query_skill_mapped("sword") != "mingwang-jian")
                return notify_fail("��û�м��������������޷�ʹ�á���������\n");

	msg = HIW "$N" HIW "���е�" + weapon->name() + HIW "����ݳ���"
              "����һ��������$n" + HIW "�������в�����Щ��ã��\n" NOR;

        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 3 || !living(target))
        {
		msg += HIG "���$p" HIG "һʱ��Ȼ���Ե��У������˼���������\n" NOR;
		target->start_busy((int)me->query_skill("sword") / 26 + 2);
	} else
        {
		msg += HIC "����$p" HIC "����ֻ����΢һ�ͣ��漴���ѣ�û�б�$P"
                       HIC "�����š�\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}