#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�᷿");
	set("long", @LONG
�����Ǻ��ι���������һ���᷿���������ι����Ŀ��˾�ס��
LONG );
	set("exits", ([
		"east" : __DIR__"hai_dayuan",
	]));

	set("sleep_room", "1");
	set("outdoors", "beijing");
	set("coor/x",-20);
	set("coor/y",960);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
