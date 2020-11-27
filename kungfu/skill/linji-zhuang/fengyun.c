// fengyun.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;        

        if (target != me)
                return notify_fail("��ֻ���÷���ׯ�����Լ���ս������\n");
		if ((int)me->query_skill("linji-zhuang", 1) < 120)
                return notify_fail("����ټ�ʮ��ׯ��򲻹�������ʩչ����ׯ��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("fengyun"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
		if ((int)me->query_temp("longhe"))
                return notify_fail("��������������ׯ�У��������з���ׯ��\n");
		if ((int)me->query_temp("daxiao"))
                return notify_fail("���������д�Сׯ�У��������з���ׯ��\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);        

        message_combatd(HIG "$N" +HIG "���˷�����ׯ����˼����Ʈ��֮���л�����Ĭ���絴��֮Ѹ�ٽ�����\n" NOR, me);

      
        me->add_temp("apply/dodge", skill / 3);       
        me->set_temp("fengyun", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("fengyun"))
        {               
                me->add_temp("apply/dodge", -amount);              
                me->delete_temp("fengyun");
                tell_object(me, "��ķ���ׯ������ϣ��������ջص��\n");
        }
}
