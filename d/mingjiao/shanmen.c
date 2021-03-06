// Room: /d/mingjiao/shanmen.c
// Date: Java 97/04/3

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "明教山门");
    set("long", @LONG
一个巨大的天然石桥横跨在两片山壁之间，石桥正上方龙盘
凤舞刻着两个大字：『明教』。字迹有些剥落，看上去年代久远。
两位三十来岁的大汉手持钢剑守在山门两侧。
LONG );
    set("exits", ([
        "westup" : __DIR__"shanlu1",
        "east" : __DIR__"tomen1",
    ]));
    set("outdoors", "mingjiao");
    set("objects",([
        __DIR__"npc/jieyinshi" : 1,
        "/kungfu/class/mingjiao/lengqian" : 1,
    ]));

    setup();
}


