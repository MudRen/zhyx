#include <ansi.h>
#include <combat.h>

#define QIAN "��" HIW "��Ӱ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
        int count;
	int i, attack_time;


	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" QIAN "��\n");

	if ((int)me->query_skill("yinshe-bianfa", 1) < 180)
		return notify_fail("������߱޷�������죬����ʩչ" QIAN "��\n");

	if (me->query("neili") < 400)
		return notify_fail("�����������������ʩչ" QIAN "��\n");

        if (me->query_skill_mapped("whip") != "yinshe-bianfa")
                return notify_fail("��û�м������߱޷�������ʩչ" QIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = MAG "$N" MAG "һ������������" + weapon->name() + MAG "��ʱ�������������ߣ�������˷�ͬʱ��$n" MAG "Ϯȥ��\n" NOR;       

	ap = me->query_skill("whip");
	dp = target->query_skill("dodge");
        attack_time = 7;

	if (ap / 2 + random(ap * 2) > dp)
	{
		msg += HIR "���$n" HIR "��$N" HIR "���˸����ֲ�����$n"
                      HIR "��æ�мܣ����нпࡣ\n" NOR;

                count = ap / 4;
                attack_time += random(3);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "�⼸����ʽ����������"
                      "�ޱȣ�ֻ�ÿ���мܡ�\n" NOR;
                count = 0;
        }
    	message_combatd(msg, me, target);        

        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count / 2);

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
		       break;
                if (! target->is_busy() && random(3) == 1)
                       target->start_busy(1); 
	        COMBAT_D->do_attack(me, target, weapon, 0); 
	}


        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count / 2);
		me->add("neili", -250);
	    me->start_busy(1 + random(attack_time / 2));
	return 1;
}
