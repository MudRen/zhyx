#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ش���ҩ������");
        set("long", @LONG
�����ǻش���ҩ�����������һ�߽��������ҩ����ζ�����滹ҪŨ��
�ܶࡣ�㿴��һ��Сͯ������������ͷ����ҩ�ġ�
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/liandan_tongzi"     : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"huichuntang",
                "north": __DIR__"liandan_yaoshi",
        ]));

        set("coor/x",-10);
	set("coor/y",1010);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
