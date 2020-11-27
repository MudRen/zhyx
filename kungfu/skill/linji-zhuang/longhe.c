// longhe.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;        

        if (target != me)
                return notify_fail("��ֻ��������ׯ�����Լ���ս������\n");
		if ((int)me->query_skill("linji-zhuang", 1) < 90)
                return notify_fail("����ټ�ʮ��ׯ��򲻹�������ʩչ����ׯ��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("longhe"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
		if ((int)me->query_temp("fengyun"))
                return notify_fail("���������з���ׯ�У�������������ׯ��\n");
		if ((int)me->query_temp("daxiao"))
                return notify_fail("���������д�Сׯ�У�������������ׯ��\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);        

        message_combatd(HIW "$N" +HIW "����������ׯ�������ţ��յػ����۾�������\n" NOR, me);

      
        me->add_temp("apply/parry", skill / 3);       
        me->set_temp("longhe", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("longhe"))
        {               
                me->add_temp("apply/parry", -amount);              
                me->delete_temp("longhe");
                tell_object(me, "�������ׯ������ϣ��������ջص��\n");
        }
}
