// File(/data/room/keep/lianwu.c) of keep's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���䳡");
	set ("long", @LONG
�˴����Ƿ���С�������䳡�����ڽ������书���򲻿ɻķϡ� 
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
    
        set("room_owner", "���ҵ�");
        set("room_name", "����С��");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "�ϴ��");
}
