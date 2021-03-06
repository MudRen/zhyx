// by yuchang

#include <ansi.h>
#include <room.h>
inherit ROOM; 

void create()
{
	set("short", "玫瑰客栈");
	set("long", @LONG       
这里是最近刚刚开业的玫瑰客栈，老板生意非常兴隆。
客栈正面的墙上挂着一块醒目的牌子(paizi)。
LONG
);	
	set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : "楼上雅房，每夜五两白银。\n",
	]));

	set("objects", ([
                __DIR__"npc/xiaoer" : 1,
	]));

	set("exits", ([
                "west" : __DIR__"shanlu",                
		  "up" : __DIR__"kedian2",
	]));
	setup();
}

int valid_leave(object me, string dir)
{

	if ( !me->query_temp("rent_paid") && dir == "up" )
		return notify_fail("怎么着，想白住啊！\n");

	if ( me->query_temp("rent_paid") && dir == "west" )
		return notify_fail("客官已经付了银子，怎么不住店就走了呢！旁人还以为小店伺候不周呢！\n");

	return ::valid_leave(me, dir);
}
