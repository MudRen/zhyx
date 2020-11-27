// tianwang.c  ��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (!living(target))
                return notify_fail("�Է��Ѿ�����ս���ˣ�\n");

        skill = me->query_skill("tianluo-diwang", 1);

        if (skill < 80)
                return notify_fail("������޵�������Ϊ����, ����ʹ�á�������������\n");

        if (me->query("neili") < 70)
                return notify_fail("��������������޷����á�������������\n");

        if (me->query_skill_mapped("hand") != "tianluo-diwang")
                return notify_fail("��û�м������޵�����, ����ʹ�á�������������\n");

        msg = HIY "$N" HIY "˫�ִ����������û������Ʒ磬Ʈ�������������������ƹ��ǹ�."
              HIC "��\n" NOR;

        me->add("neili", -30);
        ap = me->query_skill("hand");
        dp = target->query_skill("dodge");
        if (ap / 2 + random(ap) > dp)
        {
        me->start_busy(1);
                msg += HIR "$p"
                       HIR "���۾�һ������������˽�����\n" NOR;
                target->start_busy(ap / 20 + 2);
        } else
        {
                msg += CYN "����$p" CYN "�۹�һ����������$P"
                       CYN "����ͼ���������¡�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
