#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIY"�ɺ���Ӫ"NOR);
        set("long", @LONG
������ǡ��ɹš��ɺ�����Ӫ�����߷������ڽ����ʿ���ɹſɺ�
�����������������������ı�������Ĳ��ԣ����ⲻʱ���������˻��
���������ɹ�����ڽ��в������������������׼���ѷ�һ�ա�
LONG
);
        set("no_cleanup",1);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"mying",
               "north" :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}

