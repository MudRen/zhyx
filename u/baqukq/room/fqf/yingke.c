// File(/data/room/fqf/yingke.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "���ϸ��¥ӭ����");
	set ("long", @LONG
���������ϸ��¥�����˴���ӭ�Ӱ˷����͵ĵط����󷲿�����
�ݼ������ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ����
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

        set("room_owner", "����");
        set("room_name", "���ϸ��¥");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "ƽԭС·");
}
