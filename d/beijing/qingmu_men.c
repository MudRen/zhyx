#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ľ�ô���");
        set("long", @LONG
����һ������ͨ���ĺ�Ժ���ƾɵĴ��ų����ţ���������һ����Ժ��Ժ��
�����Ǽ�����ͨ����ӡ�
LONG );
       set("exits", ([
                "north" : __DIR__"yangliu3",
                "south" : __DIR__"qingmu_dayuan",
        ]));

        set("outdoors", "beijing");
        set("coor/x",-30);
	set("coor/y",960);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

