#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB"�ϻ���"NOR);
        set("long", @LONG
����������նϻ����ˣ��Ƕ����ϱ��Ľ�ͨ�ؾ�֮·������Ϊ���ұ�
��֮�أ���ɽ�����ƶ��£�ֻ��һ����խ����С������������������Ԩ��
�����ϳ����֣������鴫��
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "east"  :   __DIR__"shanlu3",
              "south" :   __DIR__"shanlu2",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

