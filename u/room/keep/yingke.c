// File(/data/room/keep/yingke.c) of keep's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "风云小筑迎客厅");
	set ("long", @LONG
这里是风云小筑的主人当家的迎接八方来客的地方。大凡客人来
拜见当家的，少不得在这里寒暄叙话，了尽仰慕之情。东面通往一个
茶室，是主人陪同客人品尝天下名茶之处。 
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

        set("room_owner", "当家的");
        set("room_name", "风云小筑");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "南大街");
}
