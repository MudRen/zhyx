#include <room.h>
inherit ROOM;

void create()
{
        set("short", "���ڶ���");
        set("long", @LONG
���ڶ�����һ�������Ĵ�֣�Ҳ�Ǳ��������ҵĵضΡ�һ����������ʯ��
�����д�����������ͷ���졣�����Ǿ����������ķ����š�
LONG );
        set("exits", ([
                "west" : __DIR__"yong_2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "beijing");
        set("coor/x",-29);
	set("coor/y",980);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

