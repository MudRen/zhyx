// File(/data/room/tntb/xiaoyuan.c) of tntb's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "¸¡ÔÆÐùÐ¡Ôº");
	set ("long", @LONG
[35mÕâÊÇÒ»¸ö²»´óµÄÔº×Ó£¬µ«ÂÌÊ÷¼ÙÉ½£¬Ê®·Ö±ðÖÂ¡£[2;37;0m
LONG );

        set("room_key", "1 of tntb");
	setup();

	set("exits", ([
                "out"    : "/d/hangzhou/yuhuangsj",
	]));

        set("outdoors", "hangzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "»Æ½ð¶þºÅ");
        set("room_owner_id", "tntb");
        set("room_name", "¸¡ÔÆÐù");
        set("room_id", "fyx");
        set("room_position", "Óñ»ÊÉ½½Å");
}
