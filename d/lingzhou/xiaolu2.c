// Room: /lingzhou/xiaolu2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����С·");
	set("long", @LONG
���Ƕ����ϵ�һ���Ӳݴ�������С·��������ƽʱûʲô�˼���
·�߿��Ų�֪����Ұ�������ߵ�������Ȼ�ߴ�ͦ�Ρ�����͸������
���������ǰ߲߰�����Ӱ�ӡ�
LONG );
	set("exits", ([
		"south"  : __DIR__"xiaolu1",
		"west"   : __DIR__"xiaolu3",
		"east"   : __DIR__"baxian",
	]));
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	set("coor/x",-2970);
	set("coor/y",3040);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

