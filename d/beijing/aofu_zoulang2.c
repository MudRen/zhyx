#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
һ��ľ�ƽṹ�����ȣ����汻������һ����Ⱦ�����ǹ⻬��������Ѿ�ߺ�
���˴��������С��ϱ��������Ĵ�����������ͨ�������ĺ�Ժ��
LONG );

	set("exits", ([
		"north" : __DIR__"aofu_houyuan",
		"south" : __DIR__"aofu_dating",
	]));
	set("objects", ([
		__DIR__"npc/jiading_a" : 1,
	]));
	set("coor/x",-30);
	set("coor/y",1085);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
