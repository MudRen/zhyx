#include <room.h>
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
����ɽ·�ϣ�ֻ������Ⱥ��������ǰ��Ⱥɽ������������
��������
LONG );
       set("exits", ([
		"northup" : "/d/jueqing/shanjiao",
		"southwest" : __DIR__"shulin",
	]));
	set("outdoors", "xiangyang");
	set("coor/x",-535);
	set("coor/y",-375);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}