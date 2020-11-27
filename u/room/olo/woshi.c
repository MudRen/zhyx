// File(/data/room/olo/woshi.c) of olo's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "太子府卧室");
	set ("long", @LONG
这是主人的卧室，收拾得井井有条。南窗下是一张大床，床边有
一个柜子，还有一个书架，上面放着一些书。整间屋子布置得非常朴
素，并不奢华。屋门在西首。 
LONG );

        set("objects", ([
                "/u/sanben/obj/locker" : 1,
        ]));

        setup();

        set("exits", ([
                "west" : __DIR__"dating",
        ]));

        create_door("west", "木门", "east", DOOR_CLOSED);
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "玄十");
        set("room_name", "太子府");
        set("room_id", "ouo");
        set("room_owner_id", "olo");
        set("room_position", "山洪瀑布");
}

