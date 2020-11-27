// shield.c �׽��ղ�����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;


        if (me->query("family/family_name") != "������")
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ���׽������\n");

        if (target != me)
                return notify_fail("��ֻ�����׽��������ղ����� \n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("yijinjing", 1) < 40)
                return notify_fail("����׽�ȼ�������\n");

        if ((int)me->query_temp("shield"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "˫ĿͻȻ��â����,�������ӿ��"
                        HIY "һ��������⡣\n" NOR, me);

        me->add_temp("apply/armor", skill * 5 / 2);
        me->set_temp("shield", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill * 5 / 2 :), skill);


        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
                me->add_temp("apply/armor", -amount);
                me->delete_temp("shield");
                tell_object(me, "���������ȥ,��ָ�ԭ�������ӡ�\n");
        }
}

