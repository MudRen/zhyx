#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��Ӣ��¥");
        set("long", @LONG
��Ӣ��¥�����������У�Ҳ����С���������ˡ���¥����
�������ڣ�װ�����繬��������������������صķ�����
�顣��С������æ�ò��ɿ������Ӵ�����ǻ�����Ŀ��ˡ�¥��
���νྻ�����п������κ��ݣ�ʮ���Ǹ��̴�֡�
LONG);
       set("exits", ([
                "north" : __DIR__"yong_1",
                "up"    : "/b/yitian/jiulou",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("outdoors", "beijing");
        set("coor/x",9);
	set("coor/y",975);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}