// File(/data/room/super/zhongting.c) of super's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "逸品堂中庭");
	set ("long", @LONG
这是逸品堂之腰：中庭，两旁便是客人居住的厢房，后面通往后
花园和主人居所，前面则是议事厅，一直通往大院。 
LONG );

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "nanhai");

        create_door("east", "木门", "west", DOOR_CLOSED);
        create_door("west", "木门", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "玄渡");
        set("room_name", "逸品堂");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "平原小路");
}

