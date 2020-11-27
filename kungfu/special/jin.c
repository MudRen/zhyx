// jin.c ��ħ����
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "��ħ����" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int i;

        if ((int)me->query_temp("special/jin"))
                return notify_fail("����ħ����֮������ʩչ���ˡ�\n");

        message_vision(HIY "$N" HIY "ʩչ����ħ����֮����ɲ�Ǽ�ȫ�������ŷ�������������֣������ޱȣ�\n" NOR, me);

        i = me->query_skill("force");

        if (i < 100)i = 100;

        me->add_temp("apply/armor", i * 3);
        me->set_temp("special/jin", 1);
        me->add_temp("apply/parry", 200);      
 
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, i * 3 :), i);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("special2/jin"))
        {
                me->add_temp("apply/armor", -amount);
                me->delete_temp("special/jin");
                me->add_temp("apply/parry", -100);
                tell_object(me, "����ħ����֮����ʩչ��ϡ�\n");
        }
        
}

