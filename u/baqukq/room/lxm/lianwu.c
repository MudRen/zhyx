// File(/data/room/lxm/lianwu.c) of lxm's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���䳡");
	set ("long", @LONG
�˴�����Ʈ��֮�ǵ����䳡�����ڽ������书���򲻿ɻķϡ� 
LONG );

	set("exits", ([
                "west" : __DIR__"houyuan",
	]));

        set("objects", ([
                "/clone/npc/mu-ren" : 4,
        ]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);

        setup();
    
        set("room_owner", "Ľ������");
        set("room_name", "Ʈ��֮��");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "�ϴ��");
}
