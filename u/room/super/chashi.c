// File(/data/room/super/chashi.c) of super's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "茶室");
	set ("long", @LONG
是一个玲珑小巧的茶室，很是显得精致。正中有一茶几，两旁立
着两个妙龄少女，正在听候主人的吩咐(tea)。 
LONG );

	set("exits", ([
		"west"  : __DIR__"yingke",
	]));

        set("objects", ([
                "/d/room/roomnpc/teagirl" : 2,
        ]));

        create_door("west", "木门", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "玄渡");
        set("room_name", "逸品堂");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "平原小路");
}
