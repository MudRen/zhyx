// File(/data/room/xiaomi/dulewu.c) of xiaomi's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "������ԴС��");
	set ("long", @LONG
���Ӳ��󣬿����ĵط�����һ�Ŵ�������һ��������ֻ�Σ��ǳ�
�򵥡�����������һ������ƽ����į���ˡ� 
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
    
        set("room_owner", "С��");
        set("room_name", "������Դ");
        set("room_id", "taoyuan");
        set("room_owner_id", "xiaomi");
        set("room_position", "�Ϻ����");
}

