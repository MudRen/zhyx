// woshi.c �ʺ������

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "����");             /* EXAMPLE */
//**    set("short", "ROOM_NAME����");
	set("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������һ��
���ӣ�����һ����ܡ�����������Ȼ���أ����ǿ���˵��������ȫ������
ȱ��ʲô������
LONG );

	set("default_long", "�������˵����ң���ʰ�þ����������ϴ�����"   /* EXAMPLE */
                            "һ�Ŵ󴲣�������һ�����ӣ�����һ����ܣ�"   /* EXAMPLE */
                            "�������һЩ�顣�������Ӳ��õ÷ǳ����أ�"   /* EXAMPLE */
                            "�����ݻ������������ס�");                   /* EXAMPLE */
                                                                         /* EXAMPLE */
	

        set("exits", ([
                "west" : __DIR__"dating",
        ]));

        create_door("west", "ľ��", "east", DOOR_CLOSED);

//**    set("objects", ([
//**            "/adm/obj/locker" : 1,
//**    ]));
//**
//**    set("sleep_room", 1);
//**    set("loving_room", 1);
        set("no_fight", 1);
        setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
