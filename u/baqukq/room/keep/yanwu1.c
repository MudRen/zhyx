// File(/data/room/keep/yanwu1.c) of keep's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "风云小筑演武厅");
	set ("long", @LONG
这是风云小筑的演武厅，有时有些江湖朋友来会，想一试身手，
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

        set("room_owner", "当家的");
        set("room_name", "风云小筑");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "南大街");
}
