// File(/data/room/huyuan/woshi.c) of huyuan's room
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
                "/u/sanben/obj/locker" : 1,
        ]));

        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
        setup();
    
        set("room_owner", "胡渊");
        set("room_name", "天剑山庄");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "草地");
}

