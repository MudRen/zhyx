// File(/data/room/addd/zuoxiang.c) of addd's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���᷿");
	set ("long", @LONG
�����ּҴ�Ժ�����᷿���ǿ��˾�ס�ĵط�����Ȼ�����ݻ���ȴ
Ҳ���õ÷ǳ����ʡ�һ�Ŵ�����ɾ���û�ж������ƣ�����������
ʵ��ʹ���ڹ���ǡ���ô��� 
LONG );

	set("exits", ([
                "west" : __DIR__"zhongting",
	]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("outdoors", "suzhou");

        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("room_owner", "����");
        set("room_name", "�ּҴ�Ժ");
        set("room_id", "lin");
        set("room_owner_id", "addd");
        set("room_position", "�ϴ��");
}
