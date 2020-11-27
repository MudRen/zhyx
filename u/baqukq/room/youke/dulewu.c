// File(/data/room/youke/dulewu.c) of youke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "游客居小屋");
	set ("long", @LONG
屋子不大，靠窗的地方摆了一张床，屋中一张桌，几只椅，非常
简单。看来主人是一个甘于平淡寂寞的人。 
LONG );

        set("objects", ([
                "/d/room/obj/storage" : 1,
        ]));

    setup();

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "游客");
        set("room_name", "游客居");
        set("room_id", "zhtx");
        set("room_owner_id", "youke");
        set("room_position", "南大街");
}

