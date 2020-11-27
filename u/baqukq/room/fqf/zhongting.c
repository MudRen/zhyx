// File(/data/room/fqf/zhongting.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "清风细雨楼中庭");
	set ("long", @LONG
这是清风细雨楼之腰：中庭，两旁便是客人居住的厢房，后面通
往后花园和主人居所，前面则是议事厅，一直通往大院。 
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

        set("room_owner", "大洋");
        set("room_name", "清风细雨楼");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "平原小路");
}

