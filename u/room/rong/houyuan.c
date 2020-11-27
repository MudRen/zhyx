// File(/data/room/rong/houyuan.c) of rong's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "后院");
	set ("long", @LONG
这是芙蓉居的后院，正中一个假山，傲然而立、非常雄伟。下有
一水池，环山而走，悠然不息。东面乃是练武之处，西面是厨房。 
LONG );

	set("exits", ([
                "south" : __DIR__"zhongting",
                "north" : __DIR__"huayuan",
                "east"  : __DIR__"lianwu",
                "west"  : __DIR__"chufang",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "水蓉儿");
        set("room_name", "芙蓉居");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "南海渔村");
}
