#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
����һ������������С����ǰ�Ų�Զ����һƬ���֣���֪
��ͨ��δ���
LONG );
       set("exits", ([
		"north" : __DIR__"shulin",
		"south" : __DIR__"guandao_2",
	]));
	set("outdoors", "xiangyang");
	set("coor/x",-540);
	set("coor/y",-385);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}