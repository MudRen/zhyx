// qing.c ��˼��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage,ap,dp;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����˼����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("tianyu-qijian", 1) < 70)
		return notify_fail("��������潣������죬����ʹ�á�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ�ʵ��̫�û���á���˼������\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�á���˼������\n");

        if (me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("��û�м��������潣��û���á���˼������\n");

	msg = HIG "$N" HIG "��������һ�������е�" + weapon->name() +
	      HIG "����һ���ʺ磬�⻪ѣĿ��������$n" HIG "��\n" NOR;

	ap = me->query_skill("sword") + me->query_skill("dodge") + me->query_str() * 10;
	dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
	ap *= me->query("combat_exp")/1000;
	dp *= target->query("combat_exp")/1000;

        if (random(ap) > random(dp) || !living(target))
	{
		damage = (int)me->query_skill("sword");
		damage += random(damage/2);

		me->add("neili", -120);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "ֻ��$N" HIR "����������峺�����ɣ��޿ײ���ؾ���$n"
                                           HIR "��$p" HIR "ֻ�������������������"
                                           "��ͷһ����Ѫ���������\n" NOR);
		target->start_busy(1+random(2));
		me->start_busy(2);
	} else 
	{
		msg += CYN "����$p" CYN "�͵���ǰһԾ,������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
		me->add("neili", -damage/2);
		me->start_busy(4);
	}
	message_combatd(msg, me, target);

	return 1;
}
