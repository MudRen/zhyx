// File(/data/room/lxm/yishiting.c) of lxm's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "������");
	set ("long", @LONG
�����Ʈ��֮������Ľ�����ź���Ҫ����������������֮������
���в������Σ����������磬�����й�����������������ͨ����������
LONG );

	set("exits", ([
                "east"   : __DIR__"yanwu1",
                "west"   : __DIR__"yanwu2",
		"north"  : __DIR__"zhongting",
                "south"  : __DIR__"yingke",
	]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "Ľ������");
        set("room_name", "Ʈ��֮��");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "�ϴ��");
}
