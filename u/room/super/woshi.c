// File(/data/room/super/woshi.c) of super's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����");
	set ("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������
һ�����ӡ��ƿ��������Կ�������Ļ�԰�������ᵽ�����㣬�ǳ�
��⡣Զ����һ��Ƭ���֡� 
LONG );

        set("exits", ([
                "down" : __DIR__"jusuo",
        ]));

        set("objects", ([
                "/u/sanben/obj/locker" : 1,
        ]));

        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
        setup();
    
        set("room_owner", "����");
        set("room_name", "��Ʒ��");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "ƽԭС·");
}

