#include <room.h>

inherit ROOM;

void create()
{
        set("short", "���ɽ·");
        set("long", @LONG
ɽ����һ��Сͤ������ͤ�������ο͵�ɽǰ����ɽ�ᶼ�ڴ�СЪ��
ɽ·�����������ϡ�������һ����·��
LONG);
        set("exits", ([
            "eastup"  : __DIR__"shanlu6",
            "west"    : __DIR__"road18",
        ]));
        set("outdoors", "hangzhou");
        set("coor/x",171);
	set("coor/y",-410);
        set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
