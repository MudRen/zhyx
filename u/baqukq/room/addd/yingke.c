// File(/data/room/addd/yingke.c) of addd's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�ּҴ�Ժӭ����");
	set ("long", @LONG
�������ּҴ�Ժ����������ӭ�Ӱ˷����͵ĵط����󷲿�������
�����ף��ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ�����ң�
��������ͬ����Ʒ����������֮���� 
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
        set("room_name", "�ּҴ�Ժ");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "�ϴ��");
}
