// sort by doing

inherit ROOM;

int do_prevent(object me);

void create()
{
	set("short", "����ϷԺ");
	set("long", @LONG
������������ĳ���ϷԺ������Ϸ����̨��(stage)��Ϸ��
̨�º�ѹѹ��һƬ�����ˡ�������������ǽ���ס�����Ȳɡ�
�����Ǻ�̨��
LONG );
	set("exits", ([
		"south" : __DIR__"xichang1",
                "up" : __DIR__"stage",
                "east" : __DIR__"houtai",
	]));
        set("item_desc", ([
		"stage" : "\n����Ϸ̨����ͻȻ�������̨���ݵĳ嶯��\n" ,
	]));
        set("objects", ([
		"/d/city2/npc/guanzho":  5,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
        if (! userp(me))
                return ::valid_leave(me, dir);

        if (dir == "up")
        {
 	        if (! me->query_temp("hastryup"))
                {
                        me->set_temp("hastryup", 1);
       	                if ((int)me->query("meili") >= 20)
		        {
	                        message_vision("ֻ��������һƬ��������"
                                               "����һ����ơ����˴���"
	                                       "˵����\n��һ�����뿴��λ" +
                                               RANK_D->query_respect(me) +
                                               "���ݡ�\n", me);
                                return ::valid_leave(me, dir);
	                } else
		        {
	                        message_vision("\nͻȻ����һӵ���ϣ���"
                                               "$N��е���ƾ��Ҳ����̨"
                                               "���£�������������" +
                                               RANK_D->query_rude(me) +
                                               "��\n", me);
                                return do_prevent(me);
                        }
                 }
                 message_vision("$Nƴ������̨ȥ��\n", me);
                 return ::valid_leave(me, dir);
        } 
        return ::valid_leave(me, dir);
}

int do_prevent(object me)
{
        int i;
        object env;
        object man, *ob;

        env = this_object();
        ob = ({ });
        if (!present("guanzhong jia", env))
	{
	        man=new(__DIR__"npc/guanzho1");
	        man->move(env);
                ob += ({ man });
	}

	if (!present("guanzhong yi", env))
	{
	        man=new(__DIR__"npc/guanzho2");
	        man->move(env);
                ob += ({ man });
	}

	if (!present("guanzhong bing", env))
	{
	        man=new(__DIR__"npc/guanzho3");
	        man->move(env);
                ob += ({ man });
	}

	if (!present("guanzhong ding", env))
	{
	        man=new(__DIR__"npc/guanzho4");
	        man->move(env);
                ob += ({ man });
	}

	if (!present("guanzhong wu", env))
	{
	        man=new(__DIR__"npc/guanzho5");
	        man->move(env);
                ob += ({ man });
	}

	for (i=0; i < sizeof(ob); i++)
        {
		ob[i]->set_leader(me);
		ob[i]->kill_ob(me);
		me->fight_ob(ob[i]);
	}

        return notify_fail("������ƴ��Ҳ��������̨��\n");
}
