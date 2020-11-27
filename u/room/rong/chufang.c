// File(/data/room/rong/chufang.c) of rong's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

string *names = ({
	"/d/shaolin/obj/mala-doufu",
	"/d/shaolin/obj/bocai-fentiao",
	"/d/shaolin/obj/shanhu-baicai",
	"/d/shaolin/obj/liuli-qiezi",
	"/d/shaolin/obj/mizhi-tianou",
	"/d/shaolin/obj/jiaxin-biji",
	"/d/shaolin/obj/basi-shanyao",
	"/d/shaolin/obj/furong-huagu",
});

void create()
{
	set("short", "����");
	set ("long", @LONG
�˴�����ܽ�ؾӵĳ�����ֻ�伸������æ��æȥ������ЪϢ�� 
LONG );

	set("exits", ([
                "east" : __DIR__"houyuan",
	]));

        set("objects", ([
                names[random(sizeof(names))] : 1,
                names[random(sizeof(names))] : 1,
                names[random(sizeof(names))] : 1,
                "/d/room/roomobj/rice"  : 2,
                "/d/room/roomobj/soup"  : 2,
                "/d/room/roomobj/mantou": 3,
                "/d/room/roomnpc/puren" : 2 + random(3),
        ]));

        set("resource/water", 1);
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ˮ�ض�");
        set("room_name", "ܽ�ؾ�");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "�Ϻ����");
}
