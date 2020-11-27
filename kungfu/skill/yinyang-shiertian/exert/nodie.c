// nodie.c ��������
// by xiner 03/3/2009
#include <ansi.h>

inherit F_CLEAN_UP;

#define NODIE "��"HIY"��������" NOR "��"

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        if ((int)me->query_skill("yinyang-shiertian", 1) < 200)
                return notify_fail("�������ʮ�������񹦵ȼ�������\n");

        if (target != me)
		return notify_fail("��ֻ��������ʮ�������������Լ���\n");

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");

	if ((int)me->query_temp("no_die"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

       if ( time() - me->query("la_sp_tm/nodie") < 3600 )        
		return notify_fail("��Ҫ��Щʱ��������ô˼��ܣ�\n");

	message_vision(YEL "$N" YEL "��ɫһ��������" NODIE YEL "��������������תʮ�����죬"
			"ȫ��ɢ����һ���⣬��ת���޺�һ�㡣\n" NOR, me);      
      
	me->set_temp("no_die",1);
	me->set("la_sp_tm/nodie", time());        
	me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 60);
	return 1;
}

void remove_effect(object me, int amount)
{
     me->delete_temp("no_die");
     tell_object(me, "��ʩչ��"NODIE"������һ������\n");
}
