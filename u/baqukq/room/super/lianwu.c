// File(/data/room/super/lianwu.c) of super's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���䳡");
	set ("long", @LONG
�˴�������Ʒ�õ����䳡�����ڽ������书���򲻿ɻķϡ� 
LONG );

	set("exits", ([
                "west" : __DIR__"houyuan",
	]));

        set("objects", ([
                "/clone/npc/mu-ren" : 4,
        ]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);

        setup();
    
        set("room_owner", "����");
        set("room_name", "��Ʒ��");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "ƽԭС·");
}
