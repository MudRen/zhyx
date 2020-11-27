#include <ansi.h>
#include <combat.h>

#define JIU "��" HIR "���ػ���" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/jiuyang-shengong/jiu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" JIU "��\n");

        if (me->query_skill("jiuyang-shengong", 1) < 200)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" JIU "��\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" JIU "��\n");

	if (me->query("reborn")) 
	{
		weapon = me->query_temp("weapon");
	        if (! objectp(weapon))
        	{
			if (me->query_skill_mapped("unarmed") != "jiuyang-shengong"
				|| me->query_skill_prepared("unarmed") != "jiuyang-shengong")
					return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" JIU "��\n");
	        }
        	else
		{
			if (objectp(weapon) && (string)weapon->query("skill_type") != "sword"
					&& (string)weapon->query("skill_type") != "blade")
					return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" JIU "��\n");
		}
	        if (objectp(weapon) && me->query_skill_mapped("sword") != "jiuyang-shengong"
        	         && (string)weapon->query("skill_type") == "sword")
				return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" JIU "��\n");
             
		else if (objectp(weapon) && (string)weapon->query("skill_type") == "blade"
                	      && me->query_skill_mapped("blade") != "jiuyang-shengong")
				return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" JIU "��\n");
	}
	else
	{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail(JIU "ֻ�ܿ���ʩչ��\n");               

	if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
		return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" JIU "��\n");
	
	if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
		return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" JIU "��\n");
	}
        if ((int)me->query("neili") < 500)
                return notify_fail("��������������޷�����" JIU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���һ������ʱһ�ɺƵ��ޱȵ����������ڱŷ���˫��"
              "��Ȼ��������$n" HIR "�������ȥ��\n" NOR;

	if (me->query("reborn"))
		ap = me->query_skill("jiuyang-shengong", 1) * 3 / 2 + me->query_con() * 20 + me->query_skill("martial-cognize") / 4;
	else
		ap = me->query_skill("jiuyang-shengong", 1) * 3 / 2 + me->query_con() * 20;

        dp = target->query_skill("parry") + target->query_con() * 18;

        if (ap * 3 / 5 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIR "$n" HIR "ֻ����Χ���������ޱȣ��ּ�����������"
                       "�Լ�Ϯ�����ٸ�ͷ��Ŀѣ����֪����εֵ���\n" NOR;

        } else
        {
                msg += HIY "$n" HIY "ֻ��$N" HIY "�����������Լ�Ϯ������"
                       "æǿ������ǿ�ֵ���\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);
	me->add_temp("apply/unarmed_damage", count / 3);
	me->add_temp("apply/damage", count / 3);

        me->add("neili", -300);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);
                if (! objectp(weapon))
                   COMBAT_D->do_attack(me, target, 0, i * 2);
                else COMBAT_D->do_attack(me, target, weapon, i * 2);
        }

        me->start_busy(3 + random(5));
        me->add_temp("apply/attack", -count);
	me->add_temp("apply/unarmed_damage", -count / 3);
	me->add_temp("apply/damage", -count / 3);

        return 1;
}
