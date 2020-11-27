#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���Լ��˹�ʹ�����Ǵ󷨡�\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");
				
		if ((int)me->query_skill("xixing-dafa", 1) < 350)
                return notify_fail("������Ǵ󷨵ȼ�������\n");	

        if ((int)me->query_temp("xixing-dafa/xiqi"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
		if ((int)me->query_temp("xixing-dafa/xijing"))
                return notify_fail("�������˹����������С�\n");
		if ((int)me->query_temp("xixing-dafa/xineili"))
                return notify_fail("�������˹����������С�\n");
		 if (me->query("family/family_name") != "�������")     
                return notify_fail("���ѷ�������̵��ӣ���Ե���ô˾�ѧ�ˡ�\n");

        skill = me->query_skill("xixing-dafa",1);
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        message_combatd(HIY "$N" HIY "�������һ����������"HIR"���������塱"HIY "����ʱȫ���������ڣ���������֡�\n" NOR, me);  
        me->set_temp("xixing-dafa/xiqi", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me)
{
        if (me->query_temp("xixing-dafa/xiqi"))
        {                
                me->delete_temp("xixing-dafa/xiqi");
                tell_object(me, "�����������������ϣ��������ջص��\n");
        }
}
