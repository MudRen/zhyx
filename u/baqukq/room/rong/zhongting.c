// File(/data/room/rong/zhongting.c) of rong's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ܽ�ؾ���ͥ");
	set ("long", @LONG
����ܽ�ؾ�֮������ͥ�����Ա��ǿ��˾�ס���᷿������ͨ����
��԰�����˾�����ǰ��������������һֱͨ����Ժ�� 
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

        set("room_owner", "ˮ�ض�");
        set("room_name", "ܽ�ؾ�");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "�Ϻ����");
}

