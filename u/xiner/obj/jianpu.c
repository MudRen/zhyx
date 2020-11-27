// jianpu.c
// Modified by xiner 01/3/2009 ���Ų��½���

inherit ITEM;

void create()
{
	set_name("���½���", ({ "canyue book", "jianpu", "book" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			"����һ�����ڲ��½����Ľ��ס�\n"
			"\n�����������ϰ(read)һ�¡�");
		set("value", 500);
		set("no_sell", 1);
		set("no_steal",1);
		set("no_put", 1);
		set("no_drop", 1);
		set("material", "silk");
	}
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_study", "read");
		remove_call_out("destroy");
		call_out("destroy", 900);
	}
}

int do_study(string arg)
{
	object me = this_player();
	int cost=10,myskill;	

	if ( arg != "canyue book" && arg != "jianpu" && arg !="book" )
		return notify_fail("��Ҫ��ʲô��\n");

	if( (int)me->query("jing") < 100 )
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
		return 1;
	}

	if (me->is_busy()) return notify_fail("��������æ���ء�\n");

	if ( me->is_fighter())
		return notify_fail("ս�����޷��Ķ���֪��\n");

	if (me->query("int") < 30)
		return notify_fail("����������Բ����޷�ѧϰ��\n");

	if( (int)me->query_skill("literate",1) < 100 )
		return notify_fail("��Ķ���д��̫���裬�޷������½�����\n");

	if( (int)me->query_skill("martial-cognize",1) < 250 )
		return notify_fail("�����ѧ����������û�а취�����½�����\n");

//	if (!me->query("reborn")) return notify_fail("����ý�������˵�Ķ���̫�����!\n");

	if ( (int)me->query_skill("canyue-sword",1) < 50)
	{
	    if ((int)me->query("jing")>cost)
	       	{
			me->receive_damage("qi", random(50) + 50);
			me->receive_damage("jing", random(50) + 50);
			me->add("neili", -100);
			me->improve_skill("canyue-sword", (me->query_skill("canyue-sword",1)+me->query("int")));
			message_vision("$N����ר���ж����½�����\n", me);
			return 1;
		}
	    else
		{
			cost=me->query("jing");
			write("�����ڹ���ƣ�룬�޷�ר�������ж����½�����\n");
		}
	}
	call_out("destroy", 1);
	return notify_fail("����Ž��׿�����ȥ���޷����������������Ľ�����\n");
}

int destroy() 
{ 
    tell_room(environment(this_object()),  
               "һ��紵����������Ϊ���̫�÷绯�ɻҽ���!\n"); 
    destruct(this_object()); 
    return 1;
}
