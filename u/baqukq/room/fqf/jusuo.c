// File(/data/room/fqf/jusuo.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "居所");
	set ("long", @LONG
这就是清风细雨楼主人大洋休息、读书的地方。楼上就是主人的
卧室，西面则是书房。 
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
    
        set("room_owner", "大洋");
        set("room_name", "清风细雨楼");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "平原小路");
}
