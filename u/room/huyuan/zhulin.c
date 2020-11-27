// File(/data/room/huyuan/zhulin.c) of huyuan's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "竹林");
	set ("long", @LONG
这里种着好大一片竹林，非常幽静。风一起就听竹叶沙沙的响，
有时胡渊就去听涛阁默听竹浪涛声，参悟武功。 
LONG );

	set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
	]));

        set("outdoors", "huanghe");
        set("sleep_room", 1);
        setup();

        set("room_owner", "胡渊");
        set("room_name", "天剑山庄");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "草地");
}
