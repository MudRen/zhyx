// room: liang.c
//Jay 4/7/96

#include <room.h>

inherit ROOM;

void create()
{ 
       set("short","���ҷ���");
       set("long", @LONG
�����������ҵķ��������¹��ƣ���Χ����Щ��ľͷ��ש�ߡ�ͻȻ��
������깴���һ�����ġ�
LONG );
        set("exits", ([
                "down" : __DIR__"mishi",
        ]));       
        set("objects", ([
                "/clone/beast/dushe" :1,
        ]));       
        setup();
	replace_program(ROOM);
}

