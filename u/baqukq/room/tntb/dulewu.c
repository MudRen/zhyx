// File(/data/room/tntb/dulewu.c) of tntb's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "������С��");
	set ("long", @LONG
[1;33m���Ӹǵ�С������Щ��������Ҳʮ�����ɣ��ؽ��ĺõط�����[2;37;0m
LONG );

        set("objects", ([
                "/d/room/obj/storage" : 1,
        ]));

    setup();

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "�ƽ����");
        set("room_name", "������");
        set("room_id", "fyx");
        set("room_owner_id", "tntb");
        set("room_position", "���ɽ��");
}

