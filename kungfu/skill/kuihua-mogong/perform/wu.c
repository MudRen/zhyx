// wu.c Ⱥħ����

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        object weapon;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("Ⱥħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��û��װ��������������һ�С�\n");
 
	if (me->query("neili") < 200)
		return notify_fail("��������������޷�ʩչȺħ���裡\n");

	if ((lvl = me->query_skill("kuihua-mogong", 1)) < 150)
		return notify_fail("��Ŀ���ħ����򲻹����޷�ʩչȺħ���裡\n");

	msg = HIR "$N" HIR "Ĭ�˿���ħ�������α������ޱȣ�������$n"
              HIR "�������У�\n" NOR;
        i = 5;
        if (lvl / 2 + random(lvl) > (int)target->query_skill("parry"))
        {
                msg += HIR "$n" HIR "ֻ������ǰһ�����������ܶ���$N"
                       HIR "����Ӱ�����ɰ������⣬�������ˡ�\n" NOR;
                count = me->query_skill("kuihua-mogong", 1) / 7;
                me->add_temp("apply/attack", count);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "���ÿ죬����"
                       "�ҵ�������æ������С��Ӧ�ԡ�\n" NOR;
                count = 0;
        }

	message_combatd(msg, me, target);
	me->add("neili", -i * 20);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 5 && ! target->is_busy())
                        target->start_busy(1);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(6));
	return 1;
}
