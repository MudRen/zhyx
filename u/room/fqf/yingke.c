// File(/data/room/fqf/yingke.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "清风细雨楼迎客厅");
	set ("long", @LONG
这里是清风细雨楼的主人大洋迎接八方来客的地方。大凡客人来
拜见大洋，少不得在这里寒暄叙话，了尽仰慕之情。东面通往一个茶
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

        set("room_owner", "大洋");
        set("room_name", "清风细雨楼");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "平原小路");
}
