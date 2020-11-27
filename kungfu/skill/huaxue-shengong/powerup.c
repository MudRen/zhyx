#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���û�Ѫ���������Լ���ս������\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        message_combatd(HIY "$N" HIY "΢һ��������Ѫ�񹦣�ȫ�������"
                        "������ɫͨ�죬�������ˡ�\n" NOR, me);
        me->add_temp("apply/attack", skill / 3);
        me->add_temp("apply/defense", skill / 3);
        me->add_temp("apply/damage", skill / 4);
        me->add_temp("apply/unarmed_damage", skill / 4);
        me->add_temp("apply/armor", skill / 3);
        me->set_temp("powerup", 1);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                           skill :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", -amount/3);
                me->add_temp("apply/defense", -amount/3);
                me->add_temp("apply/damage", -amount/4);
                me->add_temp("apply/unarmed_damage", -amount/4);
                me->add_temp("apply/armor", -amount/3);
                me->delete_temp("powerup");
                tell_object(me, "��Ļ�Ѫ��������ϣ��������ջص��\n");
        }
}

