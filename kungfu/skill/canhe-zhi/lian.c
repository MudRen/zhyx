// lian.c ����ָ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("������ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("�㲻�������������ʹ�òκ�ָ�أ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 80)
                return notify_fail("��Ĳκ�ָ��Ϊ����, ����ʹ�á�����ָ����\n");

        if (me->query("neili") < 70)
                return notify_fail("��������������޷����á�����ָ����\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û�м����κ�ָ, ����ʹ�á�����ָ����\n");

	if( me->query_skill_prepared("finger") != "canhe-zhi" )
		return notify_fail("�������Ĳ��ǲκ�ָ������ʩչ����ָ����\n");

        msg = HIC "$N" HIC "��ָ���������һ��ʢ������������ƮƮ�ķ���$n"
              HIC "��\n" NOR;

        me->add("neili", -30);
        ap = me->query_skill("finger");
        if (living(target))
              dp = target->query_skill("dodge");
        else  dp = 0;
	if (ap / 2 + random(ap) > dp)
        {
		msg += HIR "���$p" HIR "��$P"
                       HIR "�Ƶ��мܲ�������Ͼ�Թˡ�\n" NOR;
		target->start_busy(ap / 20 + 2);
	} else
        {
		msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ������һԾ���㿪����һ�С�\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}

