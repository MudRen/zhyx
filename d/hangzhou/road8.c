#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
��������ˣ����У���˽Σ�����������ϲ�������������
������������򶫱ߺ����ϱߡ������߱����ϱ�ʯɽ��
LONG);
        set("exits", ([
            "east"      : __DIR__"road9",
            "northup"   : __DIR__"baoshishan",
            "west" : __DIR__"road7",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
         set("coor/x",185);
	set("coor/y",-360);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
