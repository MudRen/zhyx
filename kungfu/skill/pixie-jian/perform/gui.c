// gui.c ������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
        int ap, dp;

	if (! target) target = offensive_target(me);

        if (me->query("gender") != "����" && !me->query("tianmo_jieti"))
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("�㲢û��ʹ�ñ�а�������޷�ʹ�ô˾��У�\n"); 

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((int)me->query_skill("pixie-jian", 1) < 100)
		return notify_fail("��ı�а������򲻹�������ʹ�ù�������\n");

	msg = HIR "$N" HIR "���Ӻ������ˣ����ι����쳣����$n"
              HIR "���Ʈ��������\n" NOR;

        ap = me->query_skill("pixie-jian", 1) * 2;
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
		msg += HIR "���$p" HIR "ֻ�ܽ����Ż����������Գ�����\n" NOR;
		target->start_busy(ap / 45 + 2);
	} else
        {
		msg += CYN "����$p" CYN "������$P" CYN "��������û"
                       "���ܵ��κ�Ӱ�졣\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
