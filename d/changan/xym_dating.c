
#include <ansi.h>

inherit ROOM;

#define PLACE "ca"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "侠义盟长安总舵");
        set("long", @LONG
这里是侠义盟在长安的总部大厅。这里没什么豪华的装饰，
一切清新素朴。正厅上方高高的悬挂着一块大匾上书侠之大者四
个金煌煌的大字。匾下的太师椅上端坐着一位威严的中年男子，
想必就是成中岳，成大当家。他与郭靖一样都是令世人景仰的大
侠。墙上挂着一个任务牌（paizi），你可以在这里领到各种任务。
LONG);

        set("objects", ([
               __DIR__"npc/boss-cheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"xym_zb",
        ]));

        setup();
}
#include <bang_good.h>

