// bojuan.c

inherit ITEM;

void create()
{
	set_name("����", ({ "bo juan", "bo", "juan" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			"����һ��������д�� ��\n"
			"ׯ�ӡ���ң�Ρ����ƣ��֮����ڤ���ߣ����Ҳ�������ɣ������ǧ�δ��֪����Ҳ��\n"
			"���ƣ��ҷ�ˮ֮��Ҳ�������为����Ҳ����������ˮ������֮�ϣ����Ϊ֮�ۣ��ñ���\n�򽺣�ˮǳ���۴�Ҳ��������\n"
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
		call_out("destroy", 300); 
	}
}

int do_study(string arg)
{
	object me = this_player();
	int cost=10,myskill;	

	if ( arg != "bo" && arg != "juan" && arg !="bo juan" )
		return notify_fail("��Ҫ��ʲô��\n");
	if( (int)me->query("jing") < 25 )
	{
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
		return 1;
	}
	if (me->is_busy()) return notify_fail("��������æ���ء�\n");

	if (me->query("dex") < 30)
		return notify_fail("��������������޷�ѧϰ�貨΢����\n");

	if( (int)me->query_skill("literate",1) < 100 )
		return notify_fail("��Ķ���д��̫���裬�޷�������д�Ķ�����\n");

        if ((int)me->query_skill("yinyang-shiertian", 1))
	{
		call_out("destroy", 1);
                return notify_fail("���ѽ��貨΢���ڻ��ͨ���ϳ�������֮����ǿ"
                                   "���书�������ٷֿ�ѧϰ�ˡ�\n");
	}

//	if (me->query("family")==0||me->query("family")["family_name"]!="��ң��") 
//		return notify_fail("��ѧ��������貨΢���������������ң�ɡ�\n");

	if ( me->is_fighter()) return notify_fail("ս�����޷��Ķ���֪��\n");

	if (!me->query("reborn")) return notify_fail("����ò�������˵�Ķ���̫�����!\n");

	if ( (int)me->query_skill("lingbo-weibu",1) < 1 )
	{
	    if ((int)me->query("jing")>cost)
	       	{
			me->receive_damage("jing", 20);
			me->improve_skill("lingbo-weibu", (me->query_skill("lingbo-weibu",1)+me->query("int")));
			message_vision("$N����ר���ж��貨΢����\n", me);
			call_out("destroy", 1);
			return 1;
		}
	    else
		{
			cost=me->query("jing");
			write("�����ڹ���ƣ�룬�޷�ר�������ж��貨΢����\n");
		}
	}
	call_out("destroy", 1);
	return notify_fail("����Ų�������ȥ���޷����������������ĵ���\n");
}

int destroy() 
{ 
    tell_room(environment(this_object()),  
               "һ��紵����������Ϊ���̫�÷绯�ɻҽ���!\n"); 
    destruct(this_object()); 
    return 1; 
}
