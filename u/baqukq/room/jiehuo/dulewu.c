// File(/data/room/jiehuo/dulewu.c) of jiehuo's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ѪӰ��С��");
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
    
        set("room_owner", "Ľ�ݽӻ�");
        set("room_name", "ѪӰ��");
        set("room_id", "xyj");
        set("room_owner_id", "jiehuo");
        set("room_position", "�ϴ��");
}

