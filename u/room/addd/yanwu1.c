// File(/data/room/addd/yanwu1.c) of addd's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "林家大院演武厅");
	set ("long", @LONG
这是林家大院的演武厅，有时有些江湖朋友来会，想一试身手，
就在这里比武较量。 
LONG );

	set("exits", ([
                "west" : __DIR__"yishiting",
	]));

        set("objects", ([
                "/clone/weapon/zhubang" : 1,
                "/clone/weapon/zhujian" : 1,
                "/clone/weapon/mudao"   : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "玄炎");
        set("room_name", "林家大院");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "南大街");
}
