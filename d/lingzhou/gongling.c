// Room: /lingzhou/deling.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
�������������ذ�˼������Ĺ���ذ�˼�������ʵ���Ǽ���˳��̫
���������������Ϊ�����˼�����Ƴ�Ҳ�Ǽ������Ĵ󽫡������Ϊ
�����Զ������ĹҲ�����������ΰ������ȥ�е��ưܡ�
LONG );
	set("exits", ([
		"south"   : __DIR__"deling",
	]));
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	set("coor/x",-2960);
	set("coor/y",3080);
	set("coor/z",-5);
	setup();
	//replace_program(ROOM);
}
