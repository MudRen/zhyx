#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ԯ����"NOR);
        set("long", @LONG
������ǡ��ɹš���Ӫפ�����ˣ�ԶԶ�ؿ��Կ�����Ӫ�ڷ���ĳ�������
ʱ�м�ƥ����ɱ��������������ٿ�����Ȼವ�һö�������ͷ�Ϸɹ�������
�Ͽ��뿪�ĺá�
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}

