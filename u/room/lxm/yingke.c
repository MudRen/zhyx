// File(/data/room/lxm/yingke.c) of lxm's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "Ʈ��֮��ӭ����");
	set ("long", @LONG
������Ʈ��֮�ǵ�����Ľ������ӭ�Ӱ˷����͵ĵط����󷲿���
���ݼ�Ľ�����ţ��ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��
һ�����ң���������ͬ����Ʒ����������֮���� 
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

        set("room_owner", "Ľ������");
        set("room_name", "Ʈ��֮��");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "�ϴ��");
}
