//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"���������"NOR);
        set("long", @LONG
���������������ڴ���ķֻᣬ���й��˺ܶ൤���ͼ��������
���е��ử���е�ĥī������һ�������ߣ������ֻӺ�����������
����������ǽ������һ������(paizi)�����������Ա������������
ȡ�ø�������ȥ��ɡ�
LONG);

        set("objects", ([ 
               __DIR__"npc/zsh_xiao"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : __DIR__"zsh_dldamen",
        ]));

        setup();
}
#include <bang_good.h>

