#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����������У�ֻ����Ⱥ�����������ܾ������ˣ��벻��
�������⾹����˷羰��
LONG );
       set("exits", ([
		"northeast" : __DIR__"shanlu1",
		"south" : __DIR__"xiaodao1",
	]));
	set("outdoors", "xiangyang");
	set("coor/x",-540);
	set("coor/y",-380);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}