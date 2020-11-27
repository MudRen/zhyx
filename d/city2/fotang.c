// fotang.c

inherit ROOM;

int do_tao(string arg);
int do_qiao(string arg);
int do_unlock(string arg);

void create()
{
	set("short", "����");
	set("long", @LONG
����һ����ã�ǽ�͵ذ嶼��ש(brick)���ġ��﹩��һ����������(foxiang)��
����ǰ��һ�Ź��������ϵ���յ�͵ơ�������Щ�谵��
LONG );
        set("outdoors", "city2");
        set("item_desc", ([
                "foxiang" :      
        "\n����һ��ͭ��������������������,��Ц���е������㡣\n",
                "brick" : "\n����ͨ��ʯש��һ��һ��Ƕ�ú�ƽ����\n",    
        ]) );
	set("exits", ([
  		"south" : "/d/city2/huayuan",
  		"east" : "/d/city2/neitang",
	]));
	set("objects", ([
  		"/d/city2/obj/table" : 1,
	]));
	set("getkey",0);
	set("getbook",0);
	setup();
}

void init()
{
  	add_action("do_qiao", "wa");
  	add_action("do_qiao", "qiao");
  	add_action("do_tao", "tao");
  	add_action("do_unlock", "open");
  	add_action("do_unlock", "unlock");
}


int do_tao(string arg)
{
	object me, ob;
	me = this_player();

	if (arg != "foxiang")
		return notify_fail("��Ҫ��ʲô��\n");

	if (me->query_temp("marks/��") )
	{
		message_vision("$N�����ڷ�������������͡�\n", me);
        	if (query("get_key") > 0)
		{
			me->receive_damage("qi", 50);
			write("�����˰��죬ʲôҲû�У������Ǳ���ȡ���ˡ�\n");
			return 1;
		}
		switch(random(5))
		{
			case 0:
				message_vision("$N����һ�����ȡ��һ��СС��������\n", me);
				message_vision("$NԾ�µ��������Ż��һ����ȴ��һöСԿ�ס�\n",me);
				ob=new("/d/city2/obj/jinyaos"); 	
 				ob->move(me);
				add("get_key", 1);
				break;
			default:
				message_vision("$N��������һ�����ʲôҲû�͵���\n",me);
 				break;
		}
		return 1;
	}
	return notify_fail("�㹻���š�\n");
}

int do_qiao(string arg)
{
	object me, ob, weapon;
	me = this_player();

	if (arg != "brick")
		return notify_fail("��Ҫ��ʲô��\n");

	if (me->query_temp("marks/��") )
	{
		if (!objectp(weapon = me->query_temp("weapon")))
			return notify_fail("���üһ���²��аɣ�\n");
		message_vision("$N�γ����У���һ�鷽ש����\n",me);
		message("vision","��ʱ¶��һ���������������и������������и�����(lock)��\n", environment(me));
		me->set_temp("marks/��",1);
		return 1;
	}
	else
		message_vision("$N�����˿�����ש�����ʲôҲû���֡�\n", this_player());
	return 1;
}

int do_unlock(string arg)
{
	object ob;
	object me;

	me = this_player();

	if (arg != "lock" )
		return notify_fail("��Ҫ��ʲô��\n");

	if (! me->query_temp("marks/��"))
		return notify_fail("�����Ķ�����\n");

	if (! objectp(ob = present("jin", me)))
	{  
		message_vision("$N�͵�һ��������������쬵�һ����һ֦�������"
			       "�����˳���������$N�ؿڡ�\n", me);
		me->die();
		return 1;
	}
	message_vision("$N����Կ��������£�ֻ������һ�������Ѵ򿪡�\n", me);
	if (query("getbook"))
		return notify_fail("��ʧ���ط������Ѿ�����ȡ����.\n");

	message_vision("$N���ֽ�ȥ������һ�����ȴ�Ǹ���������һ����\n"+
		       "����һ������ʮ���¾�����$N�̲�ס����һ����\n",
		       me);
	ob=new("/d/city2/obj/book14_5");
	set("getbook",1);
	ob->move(me);
	return 1;
}

int valid_leave(object me, string dir)
{
        me->delete_temp("marks/��");
        me->delete_temp("marks/��");
        me->delete_temp("marks/��");
        return ::valid_leave(me, dir);
}

