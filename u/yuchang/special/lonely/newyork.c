// ŦԼ��

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "ŦԼ��");
	set("long", @LONG
�����ǻ���������ֵĸۿ�ŦԼ�ۣ��Ǹù����⽻����ó��
������Ż�������ͣ�������󺣴�����ͷ����๤����������
���˻�������Ĵ����ߣ�æ�ò����ֺ�������ص��й�������
�˴�(enter chuan)�����ﻹ�����ž�������������Ů����
LONG );
	set("exits", ([		
		"west"        : __DIR__"ny_road",
	]));
       set("item_desc", ([
           "chuan" : "һ���󺣴�����Զ��û�����Ĵ��ɲ��С�\n",
       ]));
	set("objects",([	
             __DIR__"statue" : 1,
	]));
       set("no_sleep_room",1); 
	set("no_ride",1);	
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

        message_vision("�󺣴����ˣ�������ʻ���й���\n", ob);
        ob->move("/d/quanzhou/dahai");
        tell_object(ob, WHT "\nȥ���й�·;ңԶ����ֻ��ĬĬ�ȴ�.......\n\n" NOR);
        call_out("tpenghu", 10 , ob);
        return 1 ;
}

void tpenghu(object ob)
{
        if (! objectp(ob) || find_object("/d/quanzhou/dahai") != environment(ob))
                return;

        tell_object(ob, "�����������º󣬴󺣴����ڵִ����й��ļ��˸ۡ�\n\n");
        ob->move("/d/quanzhou/jiaxinggang");
}

int valid_leave(object me, string dir) 
{    
    if ( dir == "west")     
    return notify_fail("����ϸһ�룬�����Լ������������ز��죬\n"
                       "��֮���Բ�ͨ�����ǲ�Ҫ����Ϊ�á�\n\n"NOR);     
} 



