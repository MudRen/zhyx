// File(/data/room/fqf/zuoxiang.c) of fqf's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���᷿");
	set ("long", @LONG
�������ϸ��¥�����᷿���ǿ��˾�ס�ĵط�����Ȼ�����ݻ���
ȴҲ���õ÷ǳ����ʡ�һ�Ŵ�����ɾ���û�ж������ƣ����������
��ʵ��ʹ���ڹ���ǡ���ô��� 
LONG );

	set("exits", ([
                "west" : __DIR__"zhongting",
	]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("outdoors", "nanhai");

        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("room_owner", "����");
        set("room_name", "���ϸ��¥");
        set("room_id", "qfxyl");
        set("room_owner_id", "fqf");
        set("room_position", "ƽԭС·");
}
