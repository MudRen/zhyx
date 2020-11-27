// File(/data/room/fqf/zhongting.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "���ϸ��¥��ͥ");
	set ("long", @LONG
�������ϸ��¥֮������ͥ�����Ա��ǿ��˾�ס���᷿������ͨ
����԰�����˾�����ǰ��������������һֱͨ����Ժ�� 
LONG );

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "nanhai");

        create_door("east", "ľ��", "west", DOOR_CLOSED);
        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "����");
        set("room_name", "���ϸ��¥");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "ƽԭС·");
}

