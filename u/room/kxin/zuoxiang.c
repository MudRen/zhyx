// File(/data/room/kxin/zuoxiang.c) of kxin's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���᷿");
	set ("long", @LONG
�������гǵ����᷿���ǿ��˾�ס�ĵط�����Ȼ�����ݻ���ȴҲ
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

        set("room_owner", "����");
        set("room_name", "���г�");
        set("room_id", "yzc");
        set("room_owner_id", "kxin");
        set("room_position", "ƽԭС·");
}
