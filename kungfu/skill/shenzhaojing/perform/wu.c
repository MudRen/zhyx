#include <ansi.h>
#include <combat.h>

#define WU "��" HIR "��Ӱȭ��" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
	int i, attack_time;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/shenzhaojing/wu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(WU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʩչ" WU "��\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("��û�м������վ���Ϊ���ּ��ܣ��޷�ʩչ" WU "��\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("������û��׼��ʹ�����վ��񹦣��޷�ʩչ" WU "��\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 200)
                return notify_fail("������վ��񹦻�򲻹����޷�ʩչ" WU "��\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�ʩչ" WU "��\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ���㣬�޷�ʩչ" WU "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ" WU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ�����ȣ������չ�������֮��ȭ��Я��������"
              "��֮��������$n" HIR "������\n"NOR;

        ap = me->query_skill("force") + me->query_skill("martial-cognize") + me->query("str") * 10;
        dp = target->query_skill("dodge") + target->query_skill("martial-cognize") + target->query("dex") * 10;


        if (ap * 2 / 3 + random(ap) > dp)
        {
		count = ap / 10;
		attack_time = 1+(int)(me->query_skill("shenzhaojing", 1) / 40);
		msg += HIR "$n" HIR "���$P" HIR "����ɽ�����Ĺ�"
                       "�ƣ������������⣬����������������\n" NOR;
        } else
        {
		count = ap / 20;
		attack_time = 1+(int)(me->query_skill("shenzhaojing", 1) / 60);
		msg += HIC "$n" HIC "΢һ�������$P" HIC "����"
                       "ɽ�����Ĺ���ȴ˿�����ң�С���мܡ�\n" NOR;
        }

        message_combatd(msg, me, target);
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count);
        me->add("neili", -200);

	if (attack_time > 10)
		attack_time = 10;

        me->add("neili", -attack_time * 100);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

	me->start_busy(1 + random(attack_time / 5));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count);

        return 1;
}
