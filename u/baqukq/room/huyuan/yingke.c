// File(/data/room/huyuan/yingke.c) of huyuan's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�콣ɽׯӭ����");
	set ("long", @LONG
�������콣ɽׯ�����˺�Ԩӭ�Ӱ˷����͵ĵط����󷲿�������
����Ԩ���ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ�����ң�
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

        set("room_owner", "��Ԩ");
        set("room_name", "�콣ɽׯ");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "�ݵ�");
}
