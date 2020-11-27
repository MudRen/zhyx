// File(/data/room/rong/yingke.c) of rong's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ܽ�ؾ�ӭ����");
	set ("long", @LONG
������ܽ�ؾӵ�����ˮ�ض�ӭ�Ӱ˷����͵ĵط����󷲿�������
��ˮ�ض����ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ����
�ң���������ͬ����Ʒ����������֮���� 
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "ľ��", "west", DOOR_CLOSED);

        set("objects", ([
                "/d/room/roomnpc/yahuan" : 2,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ˮ�ض�");
        set("room_name", "ܽ�ؾ�");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "�Ϻ����");
}
