// �����޼�
//created by kasumi

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill,lv;
		skill = me->query_skill("chess",1);

		if (skill<300)
		      return notify_fail("������֮���������죬�޷��˹���\n");
			  
        if (target != me)
                return notify_fail("��ֻ���������޼��������Լ�����Ч�мܡ�\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("kl/wuji"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
		if ((int)me->query_temp("kl/taxue"))
                return notify_fail("���Ѿ�������̤ѩ�޺ۣ��޷�ͬʱ�����������޼��ˡ�\n");

        
        me->add("neili", -100);
        me->receive_damage("qi", 0);
		message_vision(HIW "$N΢һ�������������ķ���ֻ��$Nȫ��һ������Χ�ơ�\n" NOR, me);        
        me->add_temp("apply/parry", skill / 3);       
        me->set_temp("kl/wuji", 1);

		if ( (lv = me->query_skill("chess", 1)) >= 200 && me->query("family/family_name") == "������")
		{
			if (me->can_improve_skill("liangyi-shengong"))
			me->improve_skill("liangyi-shengong", lv * 2);
		}

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill / 3:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("kl/wuji"))
        {
                me->add_temp("apply/parry", -amount);               
                me->delete_temp("kl/wuji");
                tell_object(me, "��������޼�������ϣ��������ջص��\n");
        }
}