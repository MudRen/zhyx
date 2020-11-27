// by xiner 26/04/2009
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIR "����" HIW "��" HIR "��" NOR, ({ "hongxiu book", "book" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			"����һ�����ں������㹦�������š�\n"
			"\n�����������ϰ(read)һ�¡�");
		set("value", 0);
		set("no_sell", 1);
		set("no_steal",1);
		set("no_put", 1);
		set("material", "silk");
	}
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_study", "read");
	}
}

int do_study(string arg)
{
	object me = this_player();
	int cost;	

	if ( arg != "hongxiu book" && arg !="book" )
		return notify_fail("��Ҫ��ʲô��\n");

	if( (int)me->query("jing") < 100 )
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
		return 1;
	}

	if( (int)me->query("neili") < 100 )
	{
		write("�������������㣬�޷�ר�������ж���֪��\n");
		return 1;
	}

	if (me->is_busy()) return notify_fail("��������æ���ء�\n");

	if ( me->is_fighter())
		return notify_fail("ս�����޷��Ķ���֪��\n");

	if (me->query("int") < 30 && me->query_int() < 80)
		return notify_fail("������Բ����޷�ѧϰ��\n");

	if (me->query("mask/freequest/sew") < 301)
		return notify_fail("���Ů��̫���˲���������а��\n");		

	if( (int)me->query_skill("literate",1) < 200 )
		return notify_fail("��Ķ���д��̫���裬�޷����������㡣\n");

	if( (int)me->query_skill("martial-cognize",1) < 100 )
		return notify_fail("�����ѧ����������û�а취���������㡣\n");

	if (!me->query("reborn")) return notify_fail("�������������˵�Ķ���̫�����!\n");

	if ( (int)me->query_skill("hongxiu-tianxiang",1) < 180 &&
		me->can_improve_skill("hongxiu-tianxiang") &&
		SKILL_D("hongxiu-tianxiang")->valid_learn(me))
	{
	    cost = 100 + random(100);
	    if ((int)me->query("jing")>cost)
	       	{
			me->receive_damage("qi", cost / 2);
			me->receive_damage("jing", cost);
			me->add("neili", -cost);
			me->improve_skill("hongxiu-tianxiang", (me->query_skill("hongxiu-tianxiang",1)+me->query("int")));
			message_vision("$N����ר���ж��������㡣\n", me);
			return 1;
		}
	    else
		{
			cost=me->query("jing");
			write("�����ڹ���ƣ�룬�޷�ר�������ж��������㡣\n");
		}
	}
	return notify_fail("���޷�������ѧ���κζ�����\n");
}
