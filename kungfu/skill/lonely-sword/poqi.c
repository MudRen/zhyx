// Code of JHSH
// pojian.c ���¾Ž�������ʽ��
// qfy July 5, 1996.

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;
	int dugu_skill;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
		
	if( !objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
		return notify_fail("�������޽������ʹ�ö��¾Ž���\n");

	if( (int)me->query_skill("lonely-sword", 1) < 90 || (int)me->query("max_neili") < 400 )
		return notify_fail("��Ķ��¾Ž���������Ϊ��������δѧ�ɡ�����ʽ����\n");

        if( me->query("neili") <= 100 )
                return notify_fail("�������������\n");

	if ((int)target->query("neili") < 1)
		return notify_fail("�Է������Ѿ��ݽ��ˣ�����Ҫ��������\n");

	dugu_skill = me->query_skill("lonely-sword",1);

	msg = CYN "$NǱ�˶��¾Ž�������ʽ���������ὣʹ���������ۣ����޻��ε�ֱ��$n�ĵ��\n";
	message_vision(msg, me, target);

        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 || !living(target))
	{
		msg = HIR "$nֻ���ĵ���һ���ʹ��������й��������ŭ֮�£��������һ����Ѫ��\n" NOR;

		target->add("neili",-dugu_skill*5);
		message_vision(msg, me, target);
		target->start_busy(1+random(2));
		me->start_busy(2);
	} else {
		msg = "����$p������$P�Ľ�·�����е�����\n" NOR;
		me->start_busy(2 + random(2));
		message_vision(msg, me, target);
	}

	me->add("neili", -dugu_skill/2);

	return 1;
}
