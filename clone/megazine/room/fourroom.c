#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1; } 

void create()
{
	set("short",HIW "娱乐休息室" NOR);
	set("long", @LONG
这里是〖地狱〗杂志社提供给大家的娱乐休息室，从这里向南走是聊天室
向北是一个小花园。
LONG
	);

	set("exits", ([ 
                "down"  : __DIR__"thirdroom",
                "up"    : __DIR__"fiveroom",
                "south" : __DIR__"xiaohuayuan",
                "north" : __DIR__"lts",
        ]));

        set("objects",([ 
                "/clone/food/peanut":2, 
                "/clone/game/fxq":1, 
                "/d/taohua/obj/cha":2, 
        ])); 

        set("no_fight", 1);
	setup();
        //replace_program(ROOM);
}
