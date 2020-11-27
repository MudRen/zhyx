// File(/data/room/olo/xiaoyuan.c) of olo's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "太子府小院");
	set ("long", @LONG
这里是一个四四方方的院子，院墙都是用红砖砌成，不算高，但
是非常清爽利落。院中几棵古木成荫，隐然有一种世外桃源的感觉。
院子外面隐约是山洪瀑布，院子的北面有一扇木门。 
LONG );

        set("room_key", "1 of olo");
	setup();

	set("exits", ([
                "out"    : "/d/huashan/shanhongpb",
	]));

        set("outdoors", "huashan");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "玄十");
        set("room_name", "太子府");
        set("room_OWNER_ID", "olo");
        set("room_id", "ouo");
        set("room_position", "山洪瀑布");
}
