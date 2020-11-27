// longxiang ����֮��
// kane 25/01/99

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill, org, extra;
        string num;

        if( target != me ) 
                return notify_fail("��ֻ���������������������֮����\n");

        if( (int)me->query("neili") < 1000  ) 
                return notify_fail("�������������\n");

        if( (int)me->query("max_neili") < 2000  )
                return notify_fail("�������������\n");
/*
        if( (int)me->query_temp("shielded") ) 
                return notify_fail("���Ѿ����˻������ˡ�\n");
*/
        if( (int)me->query_temp("longxiang") )
                return notify_fail("���Ѿ���������֮���ˡ�\n");

        if ( (int)me->query_temp("powerup") )
                return notify_fail("���Ѿ������ڹ�����ս���ˡ�\n");

        if( (int)me->query_skill("longxiang", 1) < 120)
                return notify_fail("������������������\n");

        skill = me->query_skill("longxiang", 1);
        org = me->query_str();
        extra = skill/20;
        num = chinese_number(extra);
        me->add("neili", -300);

        message_vision(
        HIR"$N����Ĭ������������ԣ��ֽ�Ħ��֧���ŭӡ������"+num+"��"+num+"��֮����\n" +
        HIW"$N����ɰʯ���ݣ���Ȼ������һ����ӣ�\n"
        NOR, me);

        me->add_temp("apply/armor_vs_force", extra*8);
        me->add_temp("apply/attack", extra*8);
        me->add_temp("apply/str",  extra*2);
        me->add_temp("apply/dodge", extra);
        me->add_temp("apply/defense",  -extra*2);
        me->add_temp("apply/armor", -extra*2);

        me->set_temp("powerup", 1);
        me->set_temp("longxiang",1);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, extra :), skill/2);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{       
        int skill,extra;
         skill = me->query_skill("longxiang", 1);
         extra = skill/20;

        me->add_temp("apply/armor_vs_force", -extra*8);
        me->add_temp("apply/attack", -extra*8);
        me->add_temp("apply/str", -extra*2);
        me->add_temp("apply/dodge", -extra);
        me->add_temp("apply/defense",  extra*2);
        me->add_temp("apply/armor", extra*2);
        me->delete_temp("powerup");
        me->delete_temp("longxiang");
        tell_object(me, MAG"�������֮��������ϣ��������ջص��\n"NOR);
}

