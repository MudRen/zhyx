// File(/data/room/lxm/yanwu2.c) of lxm's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "飘渺之城演武厅");
	set ("long", @LONG
这是飘渺之城的演武厅，有时有些江湖朋友来会，想一试身手，
就在这里比武较量。 
LONG );

	set("exits", ([
                "east" : __DIR__"yishiting",
	]));

        set("objects", ([
                "/clone/weapon/zhubang" : 1,
                "/clone/weapon/zhujian" : 1,
                "/clone/weapon/mudao"   : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "慕容星雅");
        set("room_name", "飘渺之城");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "南大街");
}
