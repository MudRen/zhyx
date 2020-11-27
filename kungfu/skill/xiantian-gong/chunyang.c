// powerup.c ���칦����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���ô��������������Լ���ս������\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ������ô����������ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        message_combatd(HIY "$N΢һ�����������칦����׳�������ȫ������"
                        "�����������\n" NOR,me);
        me->add_temp("apply/attack", skill * 2 / 5);
        me->add_temp("apply/dodge", skill * 1 / 5);
        me->add_temp("apply/parry", skill * 1 / 5);
        me->set_temp("powerup", 1);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", -amount);
                me->add_temp("apply/dodge", -amount/2);
                me->add_temp("apply/parry", -amount/2);
                me->delete_temp("powerup");
                tell_object(me, "������칦������ϣ��������ջص��\n");
        }
}
