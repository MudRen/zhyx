// File(/data/room/google/dulewu.c) of google's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��ѿ��С��");
	set ("long", @LONG
���Ӳ��󣬿����ĵط�����һ�Ŵ�������һ��������ֻ�Σ��ǳ�
�򵥡�����������һ������ƽ����į���ˡ� 
LONG );

        set("objects", ([
                "/u/sanben/obj/locker" : 1,
        ]));

    setup();

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "����");
        set("room_name", "��ѿ��");
        set("room_id", "dyj");
        set("room_owner_id", "google");
        set("room_position", "�ϴ��");
}

