// Created by Kasumi

#include <ansi.h>
#define JU "��" HIY"����"HIW"����" NOR "��"

int exert(object me, object target)
{
	string msg;
	int level = me->query_skill("taiji-shengong", 1);

	if (level < 400) return notify_fail("���̫������Ϊ������ʩչ" JU "��\n");

		if( (int)me->query("neili") < 600 ) 
		return notify_fail("������������޷�ʩչ" JU "��\n");

	if( (int)me->query("jingli") == (int)me->query("max_jingli") ) 
		return notify_fail("��ľ������棬����ʩչ" JU "��\n");
	
	msg = HIY "ֻ��" + me->name()+"ϯ�ض������������죬��������������Ǳ����������������ض�����̩����\n"
		  HIY "���Ϻ��ʱ��ʱ�֣���һ�����������ĵ�վ��������\n"NOR;
	message_vision(msg, me);

	me->add("jingli", 300);
	me->add("neili", -600);
    
	if ((int)me->query("jingli") > (int)me->query("max_jingli"))
		me->set("jingli",(int)me->query("max_jingli"));

	if (me->is_fighting())
		me->start_busy(3);
	else me->start_busy(2);
	
	return 1;
}
