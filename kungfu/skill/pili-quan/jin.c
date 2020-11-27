// ���׾�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define PO "��" MAG "���׾�" NOR "��"

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/pili-quan/jin"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail(PO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("pili-quan", 1) < 40)
		return notify_fail("���������ȭ������죬�޷�ʩչ" PO "��\n");
	                        
	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷�ʩչ" PO "��\n");

        if (me->query_skill_prepared("cuff") != "pili-quan")
                return notify_fail("��û��׼��ʹ��������ȭ���޷�ʩչ" PO "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����һת��������˫ȭ��ʩ�����С�" HIW "���׾�" HIY "����˫ȭѸ���ޱ�"
              "��Ϯ��$n" HIY "��\n" NOR;

        ap = me->query_skill("cuff");
        dp = target->query_skill("parry");
	if (ap * 2 / 3 + random(ap) > dp)
	{
		damage = ap + random(ap / 2);

                me->add("neili", -120);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
		                           HIR "ֻ��$P" HIR "��һȭ��$p" HIR
                                           "���˳�ȥ�����ص�ˤ�ڵ��ϣ���Ѫ��ֹ��\n" NOR);
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
                       HIC "��һ�С�\n"NOR;
		me->add("neili", -80);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}