// File(/data/room/guoke/dulewu.c) of guoke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�޾���С��");
	set ("long", @LONG
[1;36m���Ӳ����м���һ��ɽˮ���������ĵط�����һ�Ŵ���
    ����һ��������ֻ�Σ��ǳ��򵥡�
    ̧ͷ��ϸ�����ǻ���ɽˮ���������ն����µ��޾��£�
    �Ա�������д�ţ�
    ��[1;31m��Ϸһ������ȥ�Ҵң�ǧ��ɢ��������������[1;36m����
    ��[33mһ������[1;36m����[2;37;0m
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
    
        set("room_owner", "����");
        set("room_name", "�޾���");
        set("room_id", "forever");
        set("room_owner_id", "guoke");
        set("room_position", "�Ϻ�֮��");
}

