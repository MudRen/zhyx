// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ÿ���ħ�������Լ���ս������\n");

	if ((int)me->query("neili") < 110)
		return notify_fail("�������������");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");

        if (me->query("family/master_name") == "��������")
                skill = skill * 2;

	me->add("neili", -100);

	message_combatd(HIR "$N" HIR "��ɫ������ף�а�����֣���"
                        "�о���һ����������ʧȥ��ɫ��\n" NOR, me);
       
        
	     me->add_temp("apply/attack", skill * 2 / 5);
	     me->add_temp("apply/parry", skill / 5);
	     me->add_temp("apply/dodge", skill / 5);
	     me->set_temp("powerup", 1);
       

    
    me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill /2);
	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
             
 	        me->add_temp("apply/attack", - (amount * 2 / 5));
	        me->add_temp("apply/parry", - (amount / 5));
	        me->add_temp("apply/dodge", - (amount / 5));         
           
	     me->delete_temp("powerup");
	     tell_object(me, "��Ŀ���ħ��������ϣ��������ջص��\n");
        }
}
