#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ʮ������");
	set("long", @LONG
���������������ʮ�����꣬�൱�ĺ�ΰ׳�ۡ�ʮ�������������Ͻ��ǵ�
������������������͵��������ࡣ
LONG NOR);
	set("exits", ([
		"south" : __DIR__"guandao_2",
	]));
	set("objects", ([
		__DIR__"npc/youren" : 2,
                "/clone/npc/walker" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-41);
	set("coor/y",1052);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

