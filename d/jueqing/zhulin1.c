#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + GRN "����" NOR);
        set("long", @LONG
�������Ӽ��٣������һƬ���ָ��Ǻ������Ų�������
�֣��ŵ�һ���󵭵����㣬�Ǿ����׾�����
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "southwest"   : __DIR__"shanlu2",
               "north"       : __DIR__"shiban",
        ]));

        set("no_clean_up", 0);

        set("coor/x",-525);
	set("coor/y",-350);
	set("coor/z",20);
	setup();
        //replace_program(ROOM);
}
