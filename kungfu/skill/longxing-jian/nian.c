// ��������

#include <ansi.h>

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("��������ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("hunyuan-yiqi", 1) < 150)
                return notify_fail("�����������Ԫ��������죬����ʹ���������֡�\n");
        
        if ((int)me->query_skill("buddhism", 1) < 150)
                return notify_fail("��ķ���Ϊ������죬����ʹ���������֡�\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("���Ѿ���ƣ���ߣ����������ˡ�\n");

        if ((int)me->query_temp("chang") >= 50)
                return notify_fail("���Ѿ�������̫���ˣ������Ѿ�����ˡ�\n");

        skill = me->query_skill("force");

        me->add("neili", -100);

        message_combatd(HIR "ֻ��$N" HIR "���������дʣ��������������"
                        "����$N���У�\n" NOR, me);

        me->add_temp("apply/attack", 1);
        me->add_temp("apply/dodge", 1);
        me->add_temp("apply/defense", 1);
        me->add_temp("chang", 1);

        return 1;
}

