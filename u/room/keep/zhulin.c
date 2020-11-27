// File(/data/room/keep/zhulin.c) of keep's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "竹林");
	set ("long", @LONG
这里种着好大一片竹林，非常幽静。风一起就听竹叶沙沙的响，
有时当家的就去听涛阁默听竹浪涛声，参悟武功。 
LONG );

	set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
	]));

        set("outdoors", "suzhou");
        set("sleep_room", 1);
        setup();

        set("room_owner", "当家的");
        set("room_name", "风云小筑");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "南大街");
}
