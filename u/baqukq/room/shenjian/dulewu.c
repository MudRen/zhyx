// File(/data/room/shenjian/dulewu.c) of shenjian's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��ɽׯС��");
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
    
        set("room_owner", "��");
        set("room_name", "��ɽׯ");
        set("room_id", "sjs");
        set("room_owner_id", "shenjian");
        set("room_position", "ƽԭС·");
}

