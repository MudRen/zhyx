// taotian.c �һ𽣷�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("���������졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if ((int)me->query_skill("liehuo-jian", 1) < 70)
		return notify_fail("����һ𽣷�������죬����ʹ�á��������졹��\n");
	                        
	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���Ϊ�����ߡ�\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á��������졹��\n");

        if (me->query_skill_mapped("sword") != "liehuo-jian")
                return notify_fail("������û�м����һ𽣷�������ʹ�á��������졹��\n");
			
	msg = HIR "$N" HIR "���б���һ���������һ𣬷��Ҳ���������λ�������ο࣡\n\n"
              "ɲ�Ǽ�������»����죬�������˴���ǿ��������Ĵ������\n\n"
              "$N" HIR "��Ц�£������������" + weapon->name() + "�϶�Ϊһ��ֱ��$n��ȥ�����ƾ��ˣ�\n\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 3 || !living(target))
	{
		damage = (int)me->query_skill("force") + (int)me->query_skill("sword");
        	damage = damage/2 + random(damage);
                me->add("neili", -200);
		me->receive_wound("qi",random(damage/5));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "ֻ��$N" HIR "����Ļ�⽫$n"
                                           HIR "����Χס��$n" HIR "�ĲҺ���"
                                           "����ë���Ȼ��\n" NOR);
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�͵������һԾ��������$P" HIC "�Ĺ�����Χ��\n"NOR;
		me->add("neili", -100);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
