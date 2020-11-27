// powerup.c ������ɷ������ by Kasumi

#include <ansi.h>
inherit F_SSERVER;

void snake_hit(object me, object target);

int exert(object me, object target)
{
	int skill;
	object weapon;

	if (target != me)
		return notify_fail("��ֻ�ܷ������Լ��ı����ϡ�\n");

	if ( !objectp(weapon = me->query_temp("weapon")))
               return notify_fail("�����װ�������������߲������档\n");

	if ((int)me->query("neili") < 500 )
		return notify_fail("������������޷����ߡ�\n");

	if ((int)me->query_temp("snake"))
		return notify_fail("���Ѿ��������ڱ������ˡ�\n");

	skill = me->query_skill("xiuluo-yinshagong",1)/10;
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIM "$N" HIM "�ó�һ���������ش���������ֻ����ಡ���һ����һ�����ߴܵ���" + weapon->name()+ HIM"����������\n" NOR, me);
	me->set_temp("snake", skill);
    call_out("snake_hit",1, me,target);
	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void snake_hit(object me, object target)
{
    object weapon;
	if (me->query_temp("snake") > 0)
	{
		me->set_temp("snake", me->query_temp("snake") - 1 );
		if (me->is_fighting())
		{
		}
		else
		{
			message_combatd(HIM "$N" HIM "����" + weapon->name()+ HIM"���Ų�����һ�����ߣ���˿˿��������"HIR"����"HIM"��\n" NOR, me);
		}
		remove_call_out("snake_hit");
		call_out("snake_hit",1, me,target);
		return;
	}
	else 
	{
	    me->delete_temp("snake");
		message_combatd(HIY "$N" HIY "����" + weapon->name()+ HIM"���Ų��ƵĹ��ߣ���ಡ���һ���ܵ����ϲ�������Ӱ"��\n" NOR, me);
		return;
	}
	
}

