#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
��������ˣ����У���˽Σ�����������ϲ�������������
����������򶫺��������ߣ���������һ�������
LONG);
        set("exits", ([
            	"north"     : __DIR__"dadao3",
            	"south" : __DIR__"road18",
            	"east"      : __DIR__"road20",
        ]));
        set("objects" , ([
                __DIR__"npc/dao-ke"  :1,
                __DIR__"npc/longjun" :1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "hangzhou");
        set("coor/x",170);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
