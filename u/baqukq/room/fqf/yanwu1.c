// File(/data/room/fqf/yanwu1.c) of fqf's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "清风细雨楼演武厅");
	set ("long", @LONG
这是清风细雨楼的演武厅，有时有些江湖朋友来会，想一试身手，
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

        set("room_owner", "大洋");
        set("room_name", "清风细雨楼");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "平原小路");
}
