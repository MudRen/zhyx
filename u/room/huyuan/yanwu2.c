// File(/data/room/huyuan/yanwu2.c) of huyuan's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�콣ɽׯ������");
	set ("long", @LONG
�����콣ɽׯ������������ʱ��Щ�����������ᣬ��һ�����֣�
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

        set("room_owner", "��Ԩ");
        set("room_name", "�콣ɽׯ");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "�ݵ�");
}
