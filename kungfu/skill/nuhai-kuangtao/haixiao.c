// powerup.c ��Х

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int amount1);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����ŭ�������������Լ���ս������\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "���쳤Х��������ɽ�鱬������������Ѹ���α�ȫ����\n" NOR, me);

        me->add_temp("apply/attack", skill * 2 / 5);
        me->add_temp("apply/unarmed", skill * 1 / 3);
        me->add_temp("apply/strike", skill * 1 / 3);
        me->add_temp("apply/cuff", skill * 1 / 3);
        me->add_temp("apply/claw", skill * 1 / 3);
        me->add_temp("apply/hand", skill * 1 / 3);
        me->add_temp("apply/defense", skill * 2 / 5);

        me->set_temp("powerup", 1);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 / 5, skill * 1 / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int amount1)       
{
        if (!me) return;
        if ((int)me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", - amount);
                me->add_temp("apply/unarmed", - amount1);
                me->add_temp("apply/strike", - amount1);
                me->add_temp("apply/claw", - amount1);
                me->add_temp("apply/hand", - amount1);
                me->add_temp("apply/cuff", - amount1);
                me->add_temp("apply/defense", - amount);
                me->delete_temp("powerup");
                tell_object(me, "���ŭ������������ϣ��������ջص��\n");
        }
}

