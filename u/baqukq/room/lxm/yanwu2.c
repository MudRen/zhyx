// File(/data/room/lxm/yanwu2.c) of lxm's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "Ʈ��֮��������");
	set ("long", @LONG
����Ʈ��֮�ǵ�����������ʱ��Щ�����������ᣬ��һ�����֣�
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

        set("room_owner", "Ľ������");
        set("room_name", "Ʈ��֮��");
        set("room_id", "skycity");
        set("room_owner_id", "lxm");
        set("room_position", "�ϴ��");
}
