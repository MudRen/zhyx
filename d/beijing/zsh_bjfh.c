//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "bje"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"���������"NOR);
        set("long", @LONG
���������������ڱ����ķֻᣬ����������˸����ֻ���һ����
����Ϣӭ������������һ������������һ�鼮������������������ǽ
������һ������(paizi)�����������Ա������������ȡ�ø�������ȥ
��ɡ�
LONG);

        set("objects", ([ 
               __DIR__"npc/zsh_duan"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : __DIR__"zsh_bjdamen",
        ]));

        setup();
}
#include <bang_good.h>

