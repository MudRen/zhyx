#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
��������ˣ����У���˽Σ�������������ϲ�������������
�������߿����׷塣
LONG);
        set("exits", ([
            	"northup" : __DIR__"xizhaoshan",
            	"east"    : __DIR__"road15",
            	"west"    : __DIR__"road20",
        ]));
        set("objects", ([
		__DIR__"npc/baizhen" : 1,
        ]));

        set("outdoors", "hangzhou");
        set("coor/x",185);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}