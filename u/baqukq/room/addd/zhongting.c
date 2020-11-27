// File(/data/room/addd/zhongting.c) of addd's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "林家大院中庭");
	set ("long", @LONG
这是林家大院之腰：中庭，两旁便是客人居住的厢房，后面通往
后花园和主人居所，前面则是议事厅，一直通往大院。 
LONG );

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "suzhou");

        create_door("east", "木门", "west", DOOR_CLOSED);
        create_door("west", "木门", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "玄炎");
        set("room_name", "林家大院");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "南大街");
}

