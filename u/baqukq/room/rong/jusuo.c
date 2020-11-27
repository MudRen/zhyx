// File(/data/room/rong/jusuo.c) of rong's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "居所");
	set ("long", @LONG
这就是芙蓉居主人水蓉儿休息、读书的地方。楼上就是主人的卧
室，西面则是书房。 
LONG );

	set("exits", ([
		"up"   : __DIR__"woshi",
                "west" : __DIR__"shufang",
	]));

        set("no_sleep_room", 1);
        setup();

        set("KEY_DOOR", ([
                "exit" : "east",
                "room" : __DIR__"huayuan",
        ]));
    
        set("room_owner", "水蓉儿");
        set("room_name", "芙蓉居");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "南海渔村");
}
