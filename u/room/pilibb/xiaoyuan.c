// File(/data/room/pilibb/xiaoyuan.c) of pilibb's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "霹雳堂小院");
	set ("long", @LONG
这里是一个不大的院子，角落里栽了几棵树，地上零零散散有一
些碎落叶片。院门虚掩，穿过院子就是一个小屋，非常精致。 
LONG );

        set("room_key", "1 of pilibb");
	setup();

	set("exits", ([
                "out"    : "/d/xiakedao/haibin",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "霹雳背背");
        set("room_owner_id", "pilibb");
        set("room_name", "霹雳堂");
        set("room_id", "plt");
        set("room_position", "南海之滨");
}
