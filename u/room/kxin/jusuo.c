// File(/data/room/kxin/jusuo.c) of kxin's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "居所");
	set ("long", @LONG
这就是云中城主人开心休息、读书的地方。楼上就是主人的卧室，
西面则是书房。 
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
    
        set("room_owner", "开心");
        set("room_name", "云中城");
        set("room_id", "yzc");
        set("room_owner_id", "kxin");
        set("room_position", "平原小路");
}
