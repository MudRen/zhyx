// File(/data/room/addd/zhongting.c) of addd's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�ּҴ�Ժ��ͥ");
	set ("long", @LONG
�����ּҴ�Ժ֮������ͥ�����Ա��ǿ��˾�ס���᷿������ͨ��
��԰�����˾�����ǰ��������������һֱͨ����Ժ�� 
LONG );

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "suzhou");

        create_door("east", "ľ��", "west", DOOR_CLOSED);
        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "����");
        set("room_name", "�ּҴ�Ժ");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "�ϴ��");
}

