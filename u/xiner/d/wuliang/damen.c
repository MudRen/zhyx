// damen.c
// Modified by Winder June.25 2000
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石室大门");
        set("long", @LONG
穿多岩洞，突然之间，手碰到一个冷冰冰的圆物，原来是个门环，
门环的后面象是一扇铜铁铸成的大门(men)，十分沉重。即使是臂力很
好的人，推它也觉得甚为吃力。
LONG );
	set("exits", ([
		"south" : __DIR__"yandong",
	]));
	set("item_desc", ([
		"men"  : "一扇铜铁铸成的大门，看不出来有多重。\n你可以试着用内力击(break)一下看看。\n",
	]));
	set("no_clean_up", 0);
	set("coor/x", -50020);
	set("coor/y", -21050);
	set("coor/z", -40);
	setup();
//	replace_program(ROOM);
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        object *ob, me = this_player();
        int i;

        if (arg != "men")
		return notify_fail("你在干吗? \n");

	if (me->query("neili") < 5000)
	{
		write("你运了运气，觉得自己现在的内力不济。\n");
		return 1;
	}

	me->add("neili", -2000);
        if (me->query_skill("force", 1) < 300)
        {
                message_vision(CYN "$N" CYN "呀呀嘿嘿废了半天力气，结果"
		   	       "没什么动静。\n", me);
		tell_object(me, "看来是自己的内功火候还不够。\n");
                return 1;
        }

        message_vision(CYN "铜铁大门在$N" CYN "一击之下轧轧声响，缓缓移开。\n" NOR,
		       me);

        set("exits/north",__DIR__"shishi2");
        me->add("neili", -500);
        remove_call_out("close");
        call_out("close", 5, this_object());
        return 1;
}

void close(object room)
{
        message("vision", "铜铁大门又在轧轧声响，缓缓闭上。\n"NOR, room);
        room->delete("exits/north");
}