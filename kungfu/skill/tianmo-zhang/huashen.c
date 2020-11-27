// huashen.c ������ǧ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("��������ǧ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�á�������ǧ����\n");

        skill = me->query_skill("tianmo-zhang", 1);

        if (skill < 120)
                return notify_fail("�����ħ�Ʒ���Ϊ̫�ͣ����ڲ���ʹ�á�������ǧ����\n");

        if (me->query("neili") < 100)
                return notify_fail("��������������޷�ʹ����������ǧ����\n");

        msg = HIC "$N" HIC "ͻȻ���α�죬˫�Ʒ��ɻû���������Ӱ��һ�ɾ޴�"
              HIC "���������಻�ϣ�һ���һ��ѹ��$n" HIC "��\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        me->add_temp("apply/attack", count);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(3));
        me->add_temp("apply/attack", -count);

        return 1;
}

