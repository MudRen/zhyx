// File(/data/room/jiehuo/xiaoyuan.c) of jiehuo's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ѪӰ��СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of jiehuo");
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
    
        set("room_owner", "Ľ�ݽӻ�");
        set("room_owner_id", "jiehuo");
        set("room_name", "ѪӰ��");
        set("room_id", "xyj");
        set("room_position", "�ϴ��");
}
