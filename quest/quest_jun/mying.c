#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ɹŴ�Ӫ"NOR);
        set("long", @LONG
������ǡ��ɹš�����Ӫ�ˣ��Ĵ����Ǵ��СС���ɹŰ��������һ����
����ɹŰ���Χ��������Ѳ�ߵ�����������Ӧ�����ɹſɺ�����Ӫ�ˡ�
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "north" :   __DIR__"mying1",
               "south" :   __DIR__"myuanmen1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}


