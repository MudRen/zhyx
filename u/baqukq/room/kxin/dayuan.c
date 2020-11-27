// File(/data/room/kxin/dayuan.c) of kxin's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "云中城大院");
	set ("long", @LONG
这是一个宽阔的院落，种着各种树木，阳光照下来透过树荫投下
层层影子。一条大路通向里面，踩得非常平滑的，看来是经常有人来
往。 
LONG );

	set("exits", ([
		"north"  : __DIR__"qianting",
                "out"    : "/d/xiakedao/xkroad3",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "开心");
        set("room_name", "云中城");
        set("room_OWNER_id", "kxin");
        set("room_id", "yzc");
        set("room_owner_id", "kxin");
        set("room_position", "平原小路");
}
