// tian.c ������ת

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

        if (userp(me) && !me->query("can_perform/tianmo-gun/tian"))
                return notify_fail("�㻹����ʹ�á�������ת�����С�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
           (string)weapon->query("skill_type") != "club")
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if (! me->is_fighting(target))
                return notify_fail("��������ת��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("tianmo-gun", 1);

        if (skill < 150)
                return notify_fail("�����ħ����Ϊ̫�ͣ����ڲ���ʹ�á�������ת����\n");

        if (me->query("neili") < 120)
                return notify_fail("��������������޷�ʹ����������ת����\n");

        msg = HIR "$N" HIR "Ĭ����Ԫ������" + weapon->name() +
              HIR "б����ϣ�Я���쳾����һ�����߰���$n"
              HIR "Ѹ�ٵ����\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        me->add_temp("apply/attack", count);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(3));
        me->add_temp("apply/attack", -count);

        return 1;
}

