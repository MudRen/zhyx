// dongqu.c �󽭶�ȥ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
	int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�󽭶�ȥֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query("gender") != "����")
                return notify_fail("�㲻����������,�޷�ʹ����˾�����\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if(me->query_skill_mapped("sword") != "xuantie-jian") 
                return notify_fail("��û���������������޷�ʹ�ô󽭶�ȥ��\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 100)
                return notify_fail("�����������������죬����ʹ�ô󽭶�ȥ��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʹ�ô󽭶�ȥ��\n");

	if ((int)weapon->query_weight() < 30000)
		return notify_fail("�����е�" + weapon->name() + "�����������޷�ʩչ�󽭶�ȥ��\n");

        if ((int)me->query("neili") < 300 )
                return notify_fail("����������̫��������ʹ�ô󽭶�ȥ��\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ�󽭶�ȥ��\n");

        if ((string)me->query_skill_mapped("force") != "nuhai-kuangtao")
                return notify_fail("��û�м���ŭ�������ķ����޷�ʹ������������\n");

        msg = HIC "$N" HIC "һ����ȣ����е�" + weapon->name() + HIC "����"
              "����һ������$n" HIC "��\n"NOR;

        me->start_busy(2);
            ap = me->query_skill("sword") + weapon->query_wight() / 500 + 100;
	dp = target->query_skill("force");
        if (me->query("character") == "��������")
                ap += ap / 2;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                target->start_busy(1);
            	damage = ap + random(ap/2);
		damage = me->query("jiali");
                me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$p" HIR "�����мܣ�ȴ��$P" HIR
		                           "��һ����ķ��𣬿�����Ѫ���²�ֹ��\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ����æбԾ�ܿ���\n"NOR;
                me->add("neili", -50);
        }
        message_combatd(msg, me, target);

        return 1;
}
