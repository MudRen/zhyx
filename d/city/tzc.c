#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY+BLINK"��ս��̨"NOR);
        set("long", HIC@LONG
������ר���������������ս����̨��
LONG );
        set("no_clean_up", 0);
        set("exits",([
                "down" : __DIR__"guangchang",
        ]));

        setup();
        replace_program(ROOM);
}

