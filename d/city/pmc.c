#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", HIG+BLINK"������"NOR);
    set("long", @LONG
������ר��Ϊ�����������Ʒ����ĵط���
LONG );
        set("no_fight",1);
    set("exits", ([
        "north"  : __DIR__"pm_road1",
        "out"  : __DIR__"kedian",
    ]));
    set("objects", ([
        __DIR__"npc/paimaishi" : 1,
    ]));
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}

