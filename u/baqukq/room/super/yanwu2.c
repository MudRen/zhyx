// File(/data/room/super/yanwu2.c) of super's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��Ʒ��������");
	set ("long", @LONG
������Ʒ�õ�����������ʱ��Щ�����������ᣬ��һ�����֣���
�������������� 
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

        set("room_owner", "����");
        set("room_name", "��Ʒ��");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "ƽԭС·");
}
