// shitou.c Ұ��ȭ ������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#define SHI  HIM "��ʯͷ��" NOR
#define JIAN HIR"��������" NOR
#define BU HIB"������" NOR

int perform(object me, object target)
{

        string msg;


        if (userp(me) && ! me->query("can_perform/yeqiu-quan/bu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ��"	BU "��\n");
                
        if ((int)me->query_skill("yeqiu-quan", 1) < 250)
                return notify_fail("���Ұ��ȭ��������죬����ʹ��" BU "��\n");

        if (me->query_skill_prepared("unarmed") != "yeqiu-quan"
           && me->query_skill_prepared("finger") != "yeqiu-quan"
           && me->query_skill_prepared("hand") != "yeqiu-quan"
           && me->query_skill_prepared("cuff") != "yeqiu-quan")
                return notify_fail("��û��׼��Ұ��ȭ���޷�ʹ��" BU "��\n");
                                
        if ((int)me->query("neili", 1) < 1000)
                return notify_fail("����������̫��������ʹ��" BU "��\n");

        if (userp(target))
                return notify_fail(HIW "�㲻�ܶ����ʹ�����У�\n" NOR);

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "��һ����������$n"HIG"�ȵ�������Ұ��ȭ�����һ��ʤ���ɣ�����\n\n" NOR;

	me->add("neili", -50);

	if (me->query("neili") > me->query("max_neili")/2 && target->query("neili") > target->query("max_neili")/2)
        {
	        msg += HIG "$n" HIG "���̻�Ӧ�����ã����ǿ�ʼ����\n\n" NOR;

                me->start_busy(2);
                me->add("neili", -100);
		me->start_busy(2);
		target->start_busy(2);

		msg += HIG "����ͬʱ��������һ������������\n\n"
			"$N"HIG"������ȭ��ǰһ�죬��Ȼ��һ��" BU HIG"��\n" NOR;

		switch(random(3))
		{
		case 1:
			msg += HIG"$n"HIG"����һ�죬��Ȼ����һ��" JIAN HIG"��\n" NOR;
			msg += HIC "$N��Ȼ���������ˣ�û�뵽�Ҿ�Ȼ���ˣ�\n"
				HIC "$Nֻ�����ؿ�һ�ۣ���ȻŻ�³���һ�����Ѫ��\n" NOR;
			me->add("neili", -me->query("max_neili")/2);
			break;
		case 2:
			msg += HIG"$n"HIG"����һ�죬����һ��" SHI HIG"��\n" NOR;
			msg += HIC "$n��Ȼ�������Ҿ�Ȼ���ˣ��Ҿ�ȻҲ���䣡��\n"
				HIC "$n��˵�꣬���о�Ȼ�����³���Ѫ��\n" NOR;
			target->add("neili", -target->query("max_neili")/2);
			break;
		default :
			msg += HIG"$n"HIG"����һ�죬��Ҳ����һ��" BU HIG"��\n" NOR;
			msg += HIC "$N��������һ���ȵ����������ƽ��ƽ�ˣ���\n$nҲ��������һ����\n" NOR;
			me->start_busy(1 + random(3));
			target->start_busy(1 + random(3));
			break;
		}

        } else 
        {
	        msg = HIG "����$n" HIG "ȴ��Ұ��ȭ��ʤ��������Ȥ����$N"HIG"����ս���Ų��ʼ���������\n\n" NOR;
		me->start_busy(1);
        }

        message_combatd(msg, me, target);

        return 1;
}