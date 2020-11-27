// File(/data/room/dgdg/xiaoyuan.c) of dgdg's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "喜来登小院");
	set ("long", @LONG
这里是一个不大的院子，角落里栽了几棵树，地上零零散散有一
些碎落叶片。院门虚掩，穿过院子就是一个小屋，非常精致。 
LONG );

        set("room_key", "1 of dgdg");
	setup();

	set("exits", ([
                "out"    : "/d/huanghe/caodi1",
	]));

        set("outdoors", "huanghe");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "杨六狼");
        set("room_owner_id", "dgdg");
        set("room_name", "喜来登");
        set("room_id", "xld");
        set("room_position", "草地");
}
