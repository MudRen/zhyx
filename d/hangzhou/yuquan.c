#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��Ȫ");
        set("long", @LONG
��Ȫ�½�����Ȫɽ�ϣ�ԭ�������¡��߽���Ȫ�£�ֻ�������м�
��ˮ��(pond)���������ǳ�����ɽ��·��
LONG);
        set("exits", ([
                "east"  : __DIR__"road5",
        ]));

        set("item_desc", ([
                "pond": "���Ե�ʯ�����š�������Ȫ��������ż��Сˮ��\n"
                        "��ӿ������һ�����顣\n",
        ]));

        set("objects" , ([
                __DIR__"npc/you-ke" : 1,
        ]));

        set("outdoors", "hangzhou");

        set("coor/x",165);
	set("coor/y",-360);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
