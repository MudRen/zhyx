#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"��������"NOR);
    set("long", @LONG
����һ���̵ܶ����ȣ�����ͨ��������Ϣ�ң��Ӵ��Ž���ֱ�ߣ�
�������������������
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("exits", ([
        "west"  : __DIR__"biwu_restroom",
        "south" : __DIR__"wudao1",
        "north" : __DIR__"biwu_dating",
    ]));

    set("no_clean_up", 0);
    setup();
}