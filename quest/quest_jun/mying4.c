#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"����Ӫ"NOR);
        set("long", @LONG
������ǡ��ɹš�����ѵ����Ӫ���ɹž������Թ���֮�������������
�ɹž��е�����ָ����ż����ʣ�����������ɹſɺ��صؼӵ���һƥ����
�ɹŹ�����Э����ս���ѹ��ɹſɺ��������ڱص�֮���ơ�
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "north" :   __DIR__"myuanmen2",
               "south" :   __DIR__"mying1",
               "west"  :   __DIR__"mying3",
               "east"  :   __DIR__"mying2",     
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}

