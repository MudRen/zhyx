// File(/data/room/rong/zuoxiang.c) of rong's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���᷿");
	set ("long", @LONG
����ܽ�ؾӵ����᷿���ǿ��˾�ס�ĵط�����Ȼ�����ݻ���ȴҲ
���õ÷ǳ����ʡ�һ�Ŵ�����ɾ���û�ж������ƣ�����������ʵ��
ʹ���ڹ���ǡ���ô��� 
LONG );

	set("exits", ([
                "west" : __DIR__"zhongting",
	]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("outdoors", "nanhai");

        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("room_owner", "ˮ�ض�");
        set("room_name", "ܽ�ؾ�");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "�Ϻ����");
}
