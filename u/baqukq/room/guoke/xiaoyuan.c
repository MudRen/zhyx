// File(/data/room/guoke/xiaoyuan.c) of guoke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�޾���СԺ");
	set ("long", @LONG
[1;36m������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
    Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡�
    СԺǰ�����һ�����£�һ��С·���Ѷ��ϡ�
    �������ܣ�ֻ����Զ���ľ�ʯ����д�š��޾��¡���[2;37;0m
LONG );

        set("room_key", "1 of guoke");
	setup();

	set("exits", ([
                "out"    : "/d/xiakedao/haibin",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "����");
        set("room_owner_id", "guoke");
        set("room_name", "�޾���");
        set("room_id", "forever");
        set("room_position", "�Ϻ�֮��");
}
