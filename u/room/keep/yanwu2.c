// File(/data/room/keep/yanwu2.c) of keep's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����С��������");
	set ("long", @LONG
���Ƿ���С��������������ʱ��Щ�����������ᣬ��һ�����֣�
���������������� 
LONG );

	set("exits", ([
                "east" : __DIR__"yishiting",
	]));

        set("objects", ([
                "/clone/weapon/zhubang" : 1,
                "/clone/weapon/zhujian" : 1,
                "/clone/weapon/mudao"   : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "���ҵ�");
        set("room_name", "����С��");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "�ϴ��");
}
