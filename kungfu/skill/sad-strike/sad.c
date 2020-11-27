// sad.c ��Ȼ����

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i,j;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

        if (! target || ! me->is_fighting(target))
                return notify_fail("����Ȼ���꡹ֻ����ս���жԶ���ʹ�á�\n");
 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����Ȼ���꡹ֻ�ܿ���ʹ�á�\n");
		
        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("sad-strike", 1) < 170)
                return notify_fail("�����Ȼ�����ƻ�򲻹����޷�ʹ�á���Ȼ���꡹��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ�á���Ȼ���꡹��\n");

        if (! me->query_skill_prepare() &&
            me->query_skill_mapped("unarmed") != "sad-strike" ||
            me->query_skill_prepare() &&
            me->query_skill_prepared("unarmed") != "sad-strike" &&
            me->query_skill_prepared("strike") != "sad-strike")
                return notify_fail("������û��׼��ʹ����Ȼ�����ƣ��޷�ʹ�á���Ȼ���꡹��\n");

        msg = HIM "$N" HIM "����ֹˮ����Ȼ���ˣ�����ʹ����"
              HIR "����Ȼ���ꡱ" HIM "��\n" NOR;
        ap = me->query_skill("strike") + me->query("str") * 10;
        dp = target->query_skill("parry") + target->query("dex") * 10;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                count = ap / 20;
                msg += HIY "$n" HIY "��$P" HIY "��һ�б仯Ī�⣬�����"
                       "�������ɴ��һ��������������������\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����С��$P" HIC
                       "�����У���Ų������С���мܡ�\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -200);
        j = random(6);
        if (j < 3) j = 3;
   for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me,target,me->query_temp("weapon"));
	}

        target->start_busy(1);
        me->start_busy(1 + random(4));
        me->add_temp("apply/attack", -count);

        return 1;
}
