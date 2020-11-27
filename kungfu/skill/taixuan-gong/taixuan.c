// taixuan.c ̫����

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("��̫������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(me->query_temp("weapon")))
		return notify_fail("ʩչ��̫������������֣�\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("��������������޷�ʩչ��̫��������\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʩչ��̫��������\n");

	if ((lvl = (int)me->query_skill("taixuan-gong", 1)) < 200)
		return notify_fail("���̫���񹦻������ң��޷�ʹ��̫������\n");

	msg = HIY "$N" HIY "һ�����ȣ���������ǰ����˫������ʵʵ��ץ��$n"
              HIY "��\n" NOR;

        if (lvl / 2 + random(lvl) > target->query_skill("parry") * 2 / 3)
        {
                msg += HIR "$n" HIR "����$N" HIR "����������������"
                       "��һ����һʱ���벻�ø�����мܣ�\n" NOR;
                count = lvl / 6;
                target->add_temp("apply/parry", -count);
                target->add_temp("apply/dodge", -count);
        }

	message_combatd(msg, me, target);
	me->add("neili", -120);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

        	COMBAT_D->do_attack(me, target, 0, 0);
        }

	me->start_busy(1 + random(6));
        target->add_temp("apply/parry", count);
        target->add_temp("apply/dodge", count);
	return 1;
}
