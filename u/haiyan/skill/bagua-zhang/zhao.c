// zhao.c �����ơ��֡��־�
// Create by Haiyan 2002

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����ơ��֡��־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
                
        if ((level = me->query_skill("bagua-zhang", 1)) < 100)
                return notify_fail("��İ����Ʋ�����죬����ʹ�á��֡��־���\n");

        if (me->query("neili") < 60)
                return notify_fail("�����������������޷�ʹ�á��֡��־���\n");

        msg = HIG "$N" HIG "���²����ӿ죬ʹ�������ơ��֡��־���˫��"
              "���������Ӱ����$n" HIG "�����ڵ��С�\n" NOR;

        me->add("neili", -30);
        if (random(level) > (int)target->query_skill("parry", 1) / 2)
        {
                msg += HIR "$p" HIR "ֻ��������Ӱ���Լ�Ϯ������æ���ң�"
                       "���ڵ��أ���֪�����Ӧ�ԣ�\n" NOR;
                target->start_busy(level / 30);
        } else
        {
                msg += CYN "Ȼ��$p" CYN "������$P" CYN "����ͼ������һԾ��"
                       "��������$P" CYN "�����ơ�\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

