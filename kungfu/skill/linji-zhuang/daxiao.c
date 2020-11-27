// daxiao.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;        

        if (target != me)
                return notify_fail("��ֻ���ô�Сׯ�����Լ���ս������\n");

		if ((int)me->query_skill("linji-zhuang", 1) < 150)
                return notify_fail("����ټ�ʮ��ׯ��򲻹�������ʩչ��Сׯ��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("daxiao"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
		if ((int)me->query_temp("longhe"))
                return notify_fail("��������������ׯ�У��������д�Сׯ��\n");
		if ((int)me->query_temp("fengyun"))
                return notify_fail("���������з���ׯ�У��������д�Сׯ��\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);        

        message_combatd(HIY "$N" +HIY "ϯ�ض������������죬������ض�ׯ����������������Ǳ����������������ض�����̩����\n" NOR, me);

        if (me->query_skill("jinzhong-zhao", 1) )
			me->add_temp("apply/force", skill / 5);    
		else
            me->add_temp("apply/force", skill / 3);       
        me->set_temp("daxiao", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("daxiao"))
        {       
		     if (me->query_skill("jinzhong-zhao", 1) )
				 me->add_temp("apply/force", -amount/5);
			 else
				 me->add_temp("apply/force", -amount/3);              
                me->delete_temp("daxiao");
             tell_object(me, "��Ĵ�Сׯ������ϣ��������ջص��\n");
        }
}
