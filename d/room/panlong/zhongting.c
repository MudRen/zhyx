// zhongting.c ��������ͥ

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "��ͥ");             /* EXAMPLE */
//**    set("short", "ROOM_NAME��ͥ");
	set("long", @LONG
����������֮������ͥ�����Ա��ǿ��˾�ס���᷿������ͨ����
��԰�����˾�����ǰ��������������һֱͨ����Ժ��
LONG );

	set("default_long", "����ROOM_NAME֮������ͥ�����Ա��ǿ��˾�"  /* EXAMPLE */
                            "ס���᷿������ͨ����԰�����˾�����ǰ��" /* EXAMPLE */
                            "������������һֱͨ����Ժ��");             /* EXAMPLE */
                                                                       /* EXAMPLE */

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "OUTDOORS");

        create_door("east", "ľ��", "west", DOOR_CLOSED);
        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

