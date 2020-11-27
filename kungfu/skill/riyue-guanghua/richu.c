// richu.c ���¹⻪ ֮ �ճ�����
// By haiyan

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
    int skill;

        if (me->query("gender") != "����")
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

    if (target != me)
        return notify_fail("��ֻ�������¹⻪�������Լ���Ǳ����\n");

    if ((int)me->query_skill("riyue-guanghua",1) < 100)
        return notify_fail("������¹⻪��Ϊ̫�ͣ��޷�ʩչ���ճ���������\n");

    if ((int)me->query("neili") < 200)
        return notify_fail("�������������\n");

    if ((int)me->query_temp("richu"))
        return notify_fail("���Ѿ����˹����ˡ�\n");

    skill = me->query_skill("force");
    me->add("neili", -120);
    me->receive_damage("qi", 0);
    message_combatd(HIR "$N" HIR "һ����Х��˫Ŀ��ó�죬˫��һ�㣬�����ڿն���"
                    "���ܶ�ʱ���˷�ӿ�������ѵ���\n" NOR, me);
    me->add_temp("apply/attack", skill / 3);
    me->add_temp("apply/dodge", skill / 3);
    me->add_temp("apply/parry", skill / 3);
    me->add_temp("apply/dex", skill / 20);

    me->set_temp("richu", 1);

    me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                         skill:), skill);
    if (me->is_fighting()) me->start_busy(3);

    return 1;
}

void remove_effect(object me, int amount)
{
    if (me->query_temp("richu"))
    {
        me->add_temp("apply/attack", -amount / 3);
        me->add_temp("apply/dodge", -amount / 3);
        me->add_temp("apply/parry", -amount / 3);
        me->add_temp("apply/dex", -amount / 20);
        me->delete_temp("richu");
        tell_object(me, "����ճ�����������ϣ��������ջص��\n");
    }
}

