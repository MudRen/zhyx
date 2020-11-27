// File(/data/room/keep/woshi.c) of keep's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "卧室");
	set ("long", @LONG
这是主人的卧室，收拾得井井有条。南窗下是一张大床，床边有
一个柜子。推开窗户可以看到下面的花园，还可嗅到阵阵花香，非常
惬意。远处是一大片竹林。 
LONG );

        set("exits", ([
                "down" : __DIR__"jusuo",
        ]));

        set("objects", ([
                "/d/room/obj/storage" : 1,
        ]));

        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
        setup();
    
        set("room_owner", "当家的");
        set("room_name", "风云小筑");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "南大街");
}

