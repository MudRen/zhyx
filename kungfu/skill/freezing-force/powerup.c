// powerup.c ���Ϻ�������

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ�������Լ���ս������\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        message_combatd(HIW "$N" HIW "һ����Х��������Ϻ�����һ��ɷ����Ȼ�������µ�ʱ����ɪɪ������Ҳң����缫��������\n" NOR, me);

        me->add_temp("apply/attack", skill / 3);
        me->add_temp("apply/defense", skill / 3);
        me->add_temp("apply/parry", skill / 4);
        me->add_temp("apply/dodge", skill / 4);
        me->set_temp("powerup", 1);
        me->add("neili", -100);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", - amount);
                me->add_temp("apply/defense", - amount);
                me->add_temp("apply/parry", - amount);
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("powerup");
                tell_object(me, "��ı��Ϻ���������ϣ��������ջص��\n");
        }
}

