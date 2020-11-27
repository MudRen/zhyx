// chan.c ̫��ȭ����ճ���־�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("̫��ȭ����ճ���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�á�ճ���־���\n"); 

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
                
        if ((level = me->query_skill("taiji-quan", 1)) < 200)
                return notify_fail("���̫��ȭ�������ף�����ʹ�á�ճ���־���\n");

        if (me->query("neili") < 60)
                return notify_fail("�����������������޷�ʹ�á�ճ���־���\n");

        msg = HIG "$N" HIG "ʹ��̫��ȭ����ճ���־��������ϣ�����$n"
              "���ˣ���ͼ����$n" HIG "�Ĺ��ơ�\n" NOR;

        me->add("neili", -30);
        if (random(level) > (int)target->query_skill("dodge", 1) / 2)
        {
                msg += HIR "���$p" HIR "�����ͻ�����޷�����$P" HIR "��������æ���ң�"
                       "����ʧ�룬��֪���Ӧ�ԣ�\n" NOR;
                target->start_busy(level / 30);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ��"
                       "������ˣ�δ��˿��Ӱ�졣\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

