#include <room.h>

inherit ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
��������ˣ����У���˽Σ�����������ϲ�������������
����������򶫱��������ߣ�������ʯ�ݶ���������һ��ɽ·��
LONG);
        set("exits", ([
            	"north" : __DIR__"road19",
            	"west"      : __DIR__"shiwudong",
            	"south"     : __DIR__"road17",
            	"east"      : __DIR__"yuhuangshan",
        ]));
        set("outdoors", "hangzhou");
        set("coor/x",170);
	set("coor/y",-410);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
