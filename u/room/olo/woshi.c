// File(/data/room/olo/woshi.c) of olo's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "̫�Ӹ�����");
	set ("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������
һ�����ӣ�����һ����ܣ��������һЩ�顣�������Ӳ��õ÷ǳ���
�أ������ݻ������������ס� 
LONG );

        set("objects", ([
                "/u/sanben/obj/locker" : 1,
        ]));

        setup();

        set("exits", ([
                "west" : __DIR__"dating",
        ]));

        create_door("west", "ľ��", "east", DOOR_CLOSED);
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "��ʮ");
        set("room_name", "̫�Ӹ�");
        set("room_id", "ouo");
        set("room_owner_id", "olo");
        set("room_position", "ɽ���ٲ�");
}

