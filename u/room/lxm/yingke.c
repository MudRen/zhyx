// File(/data/room/lxm/yingke.c) of lxm's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "飘渺之城迎客厅");
	set ("long", @LONG
这里是飘渺之城的主人慕容星雅迎接八方来客的地方。大凡客人
来拜见慕容星雅，少不得在这里寒暄叙话，了尽仰慕之情。东面通往
一个茶室，是主人陪同客人品尝天下名茶之处。 
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

        set("room_owner", "慕容星雅");
        set("room_name", "飘渺之城");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "南大街");
}
