#include <ansi.h>
#include <combat.h>

#define YING "��" HIR "��ϲ�ޱ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, attack_time;
        string msg;
        int ap, dp;
        int i;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/shenzhaojing/ying"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (userp(me) && ! me->query("can_perform/shenzhaojing/wu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʩչ" YING "��\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("��û�м������վ���Ϊ���ּ��ܣ��޷�ʩչ" YING "��\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("������û��׼��ʹ�����վ��񹦣��޷�ʩչ" YING "��\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 300)
                return notify_fail("������վ��񹦻�򲻹����޷�ʩչ" YING "��\n");

        if ((int)me->query_skill("unarmed", 1) < 300)
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�ʩչ" YING "��\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("���������Ϊ���㣬�޷�ʩչ" YING "��\n");

        if ((int)me->query("neili") < 1500)
                return notify_fail("��������������޷�ʩչ" YING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_combatd(HIM "\n$N" HIM "ĬĬ�������ز���������Ϊ�޹���ʥ�˲����԰���Ϊ�޹���"
                     "�𽥳�����ϲ�ޱ������龳�硣\n" NOR, me, target);

	damage = me->query_skill("shenzhaojing", 1) / 2 +
		 me->query_skill("martial-cognize", 1) +
		 me->query_temp("apply/unarmed_damage");

	damage = damage * (int)me->query_skill("zuoyou-hubo", 1) / 400;

	ap = me->query_skill("shenzhaojing",1) + me->query_skill("force") + me->query_skill("martial-cognize", 1) + me->query_skill("zuoyou-hubo", 1);
	dp = target->query_skill("dodge",1) + target->query_skill("force") + target->query_skill("martial-cognize", 1) + target->query_skill("zuoyou-hubo", 1) + target->query_skill("count", 1);

	if (me->query_skill("shenzhaojing",1)>899) me->set_skill("count", 300);

	attack_time = 1 + (int)(me->query_skill("zuoyou-hubo", 1) / 66);
	if (attack_time > 8) attack_time =8;

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
			break;

		message_combatd(HIW "$N" HIW "������Ӱ����һȭ��һ�ɻ���������ھ���ӿ���ȣ�" 
                     "������ɽ����֮����$n" HIW "ϯ�������\n" NOR, me, target);

                if (ap * 4 / 5 + random(ap) > dp)
                {
			damage = damage + random(damage/5);
			msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 15,
				HIY "$n" HIY "˼��δ����$N" HIY "���ھ���������룬"
				"$n" HIY "�ܴ��ػ������һ��Ż������" HIR "��Ѫ" HIY "��\n" NOR);
                } else
                {
                        msg = CYN "$n" CYN "����˫�ۣ������мܣ���"
                              "$N" CYN "���ھ�ж����\n" NOR;
                }

                message_combatd(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }
        me->start_busy(3+random(4));
        me->add("neili", -1000);

	if (me->query_skill("count",1)>0) me->delete_skill("count");

        return 1;
}
