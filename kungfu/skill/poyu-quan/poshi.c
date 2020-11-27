// poshi.c ��ʯһ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

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
	if (! target || ! me->is_fighting(target))
		return notify_fail("����ʯһ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("ֻ�п��ֲ���ʹ������ȭ��\n");

	if ((int)me->query_skill("poyu-quan", 1) < 120)
		return notify_fail("�������ȭ������죬����ʹ�á���ʯһ������\n");

        if ((int)me->query_skill("zixia-shengong",1) < 120)
                return notify_fail("�����ϼ����Ϊ��������\n");
	                        
	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ�������ߣ��������á���ʯһ������\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á���ʯһ������\n");
			
	msg = HIY "$N" HIY "���һ�����ս���ȭͷ����һ�㵭������ɫ��������������صĻ���$n" HIY "��\n"NOR;

       ap = me->query_skill("force") + me->query("str") * 10;
       dp = target->query_skill("force") + target->query("str") * 10;

        if (ap / 2 + random(ap) > dp || !living(target))
	{
                damage = ap + (int)me->query_skill("cuff");
                damage = damage / 3;
                damage += random(damage);

		me->add("neili", -200);
              msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
		                           HIR "ֻ��$P" HIR "����ȭ��ͬӲ����ҵ�$p" HIR
                                           "���˳�ȥ�����ص�ˤ�ڵ��ϣ���Ѫ��ֹ��\n" NOR);
		me->start_busy(2);
                target->start_busy(1+random(2));
	} else 
	{
		msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
                       HIC "��һ�С�\n"NOR;
		me->add("neili", -100);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
