// Room: /lingzhou/luorilin1.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
������λ�����ݵĶ�������������������ݵ��м䣬��������
�����Ǻ��ɡ�
LONG );
	set("exits", ([
		"north"     : __DIR__"dalu",
		"southwest" : __DIR__"dongmen",
	]));
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	set("coor/x",-2970);
	set("coor/y",3010);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
