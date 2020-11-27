// File(/data/room/addd/jusuo.c) of addd's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "居所");
	set ("long", @LONG
这就是林家大院主人玄炎休息、读书的地方。楼上就是主人的卧
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
    
        set("room_owner", "玄炎");
        set("room_name", "林家大院");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "南大街");
}
