// File(/data/room/fqf/jusuo.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
��������ϸ��¥���˴�����Ϣ������ĵط���¥�Ͼ������˵�
���ң����������鷿�� 
LONG );

	set("exits", ([
		"up"   : __DIR__"woshi",
                "west" : __DIR__"shufang",
	]));

        set("no_sleep_room", 1);
        setup();

        set("KEY_DOOR", ([
                "exit" : "east",
                "room" : __DIR__"huayuan",
        ]));
    
        set("room_owner", "����");
        set("room_name", "���ϸ��¥");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "ƽԭС·");
}
