#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
������һ����������Ĵ�ٵ��ϡ���ʱ��������������߷ɳ۶�������
��һ·��������·��������������������֡�
LONG );
       set("exits", ([
		"east" : __DIR__"shi_2",
		"north" : __DIR__"guandao_2",
	]));
	set("objects", ([
		__DIR__"npc/tangzi" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-41);
	set("coor/y",1050);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

