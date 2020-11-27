#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{               
        int skill;      
        if (me->query_temp("gang")) 
                return notify_fail(HIG "���Ѿ����˻�Ԫ����ˡ�\n" NOR);
                
        if ((int)me->query("neili") < 400)
                return notify_fail("���������������\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("��Ļ�����������Ϊ����������ʹ�û�Ԫ���! \n");

		message_combatd(HIW "$N" HIW "ʹ������������ѧ����Ԫ�����һ�ɰ����Զ������跢ɢ���£�ȫ�������ڰ�ɫ�����У�\n" NOR, me);             
        
        skill = me->query_skill("force");
		me->add_temp("apply/unarmed_damage", skill / 5);
        me->add("neili", -100);
		me->set_temp("gang", 1);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        if (me->is_fighting()) me->start_busy(2);
        return 1;
}

void remove_effect(object me, int skill)
{
        if ((int)me->query_temp("gang")) 
        {
                me->add_temp("apply/unarmed_damage", -(skill / 5));
                me->delete_temp("gang");
                tell_object(me, HIY "��Ļ�Ԫ���������ϣ��������ջص��\n" NOR);
        }
}

