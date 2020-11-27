// File(/data/room/super/lianwu.c) of super's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "练武场");
	set ("long", @LONG
此处便是逸品堂的练武场，人在江湖，武功万万不可荒废。 
LONG );

	set("exits", ([
                "west" : __DIR__"houyuan",
	]));

        set("objects", ([
                "/clone/npc/mu-ren" : 4,
        ]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);

        setup();
    
        set("room_owner", "玄渡");
        set("room_name", "逸品堂");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "平原小路");
}
