// Room: /d/quanzhou/jiaxinggang.c
// Date: May 7, 96   Jay
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "嘉兴海港");
	set("long", @LONG
这里是嘉兴海港，港内白帆点点，码头上停着好多渔船，可是
一提起桃花岛却个个摇头。这里还停泊着几艘大海船(chuan),若想
前往花旗国的纽约港可在此处(enter chuan)。
LONG );
	set("exits", ([
                "west" : __DIR__"nanhu",
	]));
       set("item_desc", ([
                "chuan" : "一条大海船。出远海没这样的船可不行。\n",
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
                tell_object(ob, "你要去哪儿？\n" );
                return 1;
        }    

        message_vision("船夫升起帆，大海船就向东方开始慢慢航行。\n", ob);
        ob->move(__DIR__"dahai");
        tell_object(ob, WHT "\n去往花旗国路途遥远，你只好默默等待.......\n\n" NOR);
        call_out("tpenghu", 10 , ob);
        return 1 ;
}

void tpenghu(object ob)
{
        if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
                return;

        tell_object(ob, "航行了两个月后，大海船终于抵达了花旗国的纽约港。\n\n");
        ob->move("/u/sanben/special/lonely/newyork");
}



