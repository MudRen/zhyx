// Room: /d/quanzhou/jiaxinggang.c
// Date: May 7, 96   Jay
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���˺���");
	set("long", @LONG
�����Ǽ��˺��ۣ����ڰ׷���㣬��ͷ��ͣ�źö��洬������
һ�����һ���ȴ����ҡͷ�����ﻹͣ���ż��Ҵ󺣴�(chuan),����
ǰ���������ŦԼ�ۿ��ڴ˴�(enter chuan)��
LONG );
	set("exits", ([
                "west" : __DIR__"nanhu",
	]));
       set("item_desc", ([
                "chuan" : "һ���󺣴�����Զ��û�����Ĵ��ɲ��С�\n",
       ]));
	set("objects", ([
		"/d/taohua/npc/chuanfu": 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "quanzhou");
	setup();	
}

void init()
{
        add_action("do_enter", "enter");
}


int do_enter(string arg)
{
        object ob ;
        string dir;

        ob = this_player();
        if (arg !="chuan")
        {
                tell_object(ob, "��Ҫȥ�Ķ���\n" );
                return 1;
        }    

        message_vision("�������𷫣��󺣴����򶫷���ʼ�������С�\n", ob);
        ob->move(__DIR__"dahai");
        tell_object(ob, WHT "\nȥ�������·;ңԶ����ֻ��ĬĬ�ȴ�.......\n\n" NOR);
        call_out("tpenghu", 10 , ob);
        return 1 ;
}

void tpenghu(object ob)
{
        if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
                return;

        tell_object(ob, "�����������º󣬴󺣴����ڵִ��˻������ŦԼ�ۡ�\n\n");
        ob->move("/u/sanben/special/lonely/newyork");
}



