// File(/data/room/google/xiaoyuan.c) of google's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��ѿ��СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of google");
	setup();

	set("exits", ([
                "out"    : "/d/suzhou/nandajie3",
	]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "����");
        set("room_owner_id", "google");
        set("room_name", "��ѿ��");
        set("room_id", "dyj");
        set("room_position", "�ϴ��");
}
