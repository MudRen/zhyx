#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������ͬ");
	set("long", @LONG
������������ͬ������ߵ��������Խ���İ�����������խ��ͨ����
�ڲ��ϵ����ϱ����졣
LONG );
       set("exits", ([
		"north" : __DIR__"yangliu1",
		"south" : __DIR__"yangliu3",
	]));

	set("outdoors", "beijing");
	set("coor/x",-30);
	set("coor/y",980);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

