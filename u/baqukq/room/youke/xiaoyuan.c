// File(/data/room/youke/xiaoyuan.c) of youke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�ο;�СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of youke");
	setup();

	set("exits", ([
                "out"    : "/d/suzhou/nandajie1",
	]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "�ο�");
        set("room_owner_id", "youke");
        set("room_name", "�ο;�");
        set("room_id", "zhtx");
        set("room_position", "�ϴ��");
}