// po.c ���־�

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
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("���á����־������б����е���\n");

	if ((int)me->query_skill("hujia-daofa", 1) < 90)
		return notify_fail("��ĺ��ҵ���������죬����ʹ�á����־�����\n");
	                        
	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ�����ߡ�\n");
			
	if( (int)me->query("neili") < 500 )
		return notify_fail("����������̫��������ʹ�á����־�����\n");
			
	msg = HIM "$N" HIM "���е�" + weapon->name() +
              HIM "����һת��һ�����ε�����Ȼ��Ϣ��Ϯ��$n" HIM "��\n"NOR;

        ap = me->query_skill("blade") + me->query_skill("force");
        if (living(target))
                dp = target->query_skill("force");
        else    dp = 0;

        if (ap / 4 + random(ap / 3) > dp)
	{
		damage = ap + random(ap / 2);
                me->add("neili", -damage/2);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "ֻ��$n" HIR "һ���ҽУ�����������"
                                           "�����������Ѫ���������\n" NOR);
		me->start_busy(2);
		target->start_busy(1 + random(2));
	} else 
	{
		msg += HIC "����$p" HIC "Ĭ��������Ӳ�ǵֵ���$P"
                       HIC "��������ε�����\n"NOR;
                me->add("neili", -100);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
