// File(/data/room/kxin/yishiting.c) of kxin's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "������");
	set ("long", @LONG
��������г����˿��ĺ���Ҫ����������������֮���������в�
�����Σ����������磬�����й�����������������ͨ���������� 
LONG );

	set("exits", ([
                "east"   : __DIR__"yanwu1",
                "west"   : __DIR__"yanwu2",
		"north"  : __DIR__"zhongting",
                "south"  : __DIR__"yingke",
	]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "����");
        set("room_name", "���г�");
        set("room_id", "yzc");
        set("room_owner_id", "kxin");
        set("room_position", "ƽԭС·");
}
