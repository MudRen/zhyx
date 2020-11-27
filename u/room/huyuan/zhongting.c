// File(/data/room/huyuan/zhongting.c) of huyuan's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�콣ɽׯ��ͥ");
	set ("long", @LONG
�����콣ɽׯ֮������ͥ�����Ա��ǿ��˾�ס���᷿������ͨ��
��԰�����˾�����ǰ��������������һֱͨ����Ժ�� 
LONG );

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "huanghe");

        create_door("east", "ľ��", "west", DOOR_CLOSED);
        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "��Ԩ");
        set("room_name", "�콣ɽׯ");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "�ݵ�");
}

