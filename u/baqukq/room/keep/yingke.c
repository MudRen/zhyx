// File(/data/room/keep/yingke.c) of keep's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����С��ӭ����");
	set ("long", @LONG
�����Ƿ���С�������˵��ҵ�ӭ�Ӱ˷����͵ĵط����󷲿�����
�ݼ����ҵģ��ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ��
���ң���������ͬ����Ʒ����������֮���� 
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

        set("room_owner", "���ҵ�");
        set("room_name", "����С��");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "�ϴ��");
}
