#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ڳ�������ĳ������ϣ���·��������������������֣���ʱ������
��������߷ɳ۶���������һ·���������߾��ǳ������ˣ����߲�Զ���Ƿ�
������������֣��������У�ʮ�����֡�
LONG );
       set("exits", ([
		"west" : __DIR__"chaoyang_dao1",
		"east" : __DIR__"chaoyangmen",
	]));
	set("objects", ([
		__DIR__"npc/tiaofu" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",40);
	set("coor/y",1020);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

