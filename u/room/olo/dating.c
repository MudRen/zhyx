// File(/data/room/olo/dating.c) of olo's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "̫�Ӹ�����");
	set ("long", @LONG
�����̫�Ӹ�������ʮӭ�Ϳ��˵ĵط���������Щ���Σ�������
�������硣������������ʮ�ķ��䣬��һ��ľ�������š��ϱ��Ǵ��ţ�
��ȥ����Ժ�ӡ� 
LONG );

	setup();

	set("exits", ([
                "east"   : __DIR__"woshi",
		"north"  : __DIR__"houyuan",
	]));

        create_door("east", "ľ��", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("room_owner", "��ʮ");
        set("room_name", "̫�Ӹ�");
        set("room_id", "ouo");
        set("room_position", "ɽ���ٲ�");
}
