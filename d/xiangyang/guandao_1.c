#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
������һ����������Ĵ�ٵ��ϡ���ʱ��������������
�߷ɳ۶���������һ·��������·��������������������֡�
LONG );
       set("exits", ([
		"east" : __DIR__"westgate2",
		"north" : __DIR__"guandao_2",
	]));
	set("outdoors", "xiangyang");
	set("coor/x",-540);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

