// File(/data/room/rong/yingke.c) of rong's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "芙蓉居迎客厅");
	set ("long", @LONG
这里是芙蓉居的主人水蓉儿迎接八方来客的地方。大凡客人来拜
见水蓉儿，少不得在这里寒暄叙话，了尽仰慕之情。东面通往一个茶
室，是主人陪同客人品尝天下名茶之处。 
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("objects", ([
                "/d/room/roomnpc/yahuan" : 2,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "水蓉儿");
        set("room_name", "芙蓉居");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "南海渔村");
}
