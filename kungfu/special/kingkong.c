//kingkong.c �������

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIR "�������" NOR; }



#define KINGKONG "��" HIR "�������" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp, count;

        if (! me->query("reborn"))        
            return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");

        if (! me->is_fighting())
                return notify_fail(KINGKONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        target = me->select_opponent();

        if (! target || ! target->is_character()
           || target->query("not_living"))
                return notify_fail("������˭ʩչ" KINGKONG  "��\n");

//	if ( ! target->query_temp("no_die") )
//		return notify_fail("�Է���û������������ѽ ��\n");

	if ( ! target->query_temp("no_die") )
	{
		if ((int)me->query_temp("jingang"))
			return notify_fail("���Ѿ����˹����ˡ�\n");

		if ((int)me->query("neili") < 500)
			return notify_fail("��������������޷�ʩչ��������ա���\n");

		message_vision( HIR "$N" HIR "��ɫͻȻ��ó�죬ȫ������ȫ�������ֱۣ�"
			"�ܲ����������$n��\n\n" NOR, me, target);

		count = (int)me->query("str");
		me->add_temp("str", count);
		me->set_temp("jingang", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect", me, count :), 50);
		me->add("neili", -500);

	}
	else
	{
		message_vision( HIR "$N" HIR "��ɫͻȻ��ó�죬˫�ֹ���޴�������"
			"����һ��Ϯ��$n��\n\n" NOR, me, target);

		ap = me->query_str(); 
		dp = target->query_con();

		if ( ap / 2 + random(ap) > dp )
		{
			target->delete_temp("no_die");

			message_vision(CYN"ֻ��$n" CYN"�ƺ�һ����"
				"����������$N������\n\n"NOR, me, target);

			tell_object(target, HIW"��Ĳ�������"NOR + me->name() 
        	                + HIW"�Ƴ��ˣ�\n\n"NOR);           
		} else
			message_vision(HIY"ֻ��$n" HIY"Ӳ��������$N��һ�У�"
                	            "��������˿����Ϊ������\n\n"NOR, me, target);
		me->start_busy(3 + random(3));
	}
	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("jingang"))
	{
		me->add_temp("str", -amount);
		me->delete_temp("jingang");
		tell_object(me, HIR "��о�˫���е��������Ĵ�������ɫ�𽥻ָ�������\n"NOR);
	}
}
