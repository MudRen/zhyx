#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", BLK"��ʯ��"NOR);
        set("long", @LONG
���������ʯ���ˣ���˵���������ص��������£������ԭ���
�޴ӿ����ˣ����������κ��ɹ�����ս�𣬱߾�������������������
�ͳ����˼�����֮���ˡ�
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "north" :   __DIR__"shanlu2",
              "south" :   __DIR__"shanlu1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}


