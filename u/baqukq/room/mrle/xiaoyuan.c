// File(/data/room/mrle/xiaoyuan.c) of mrle's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "���ɾ�СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of mrle");
	setup();

	set("exits", ([
                "out"    : "/d/xiakedao/xkroad3",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "Ľ�����");
        set("room_owner_id", "mrle");
        set("room_name", "���ɾ�");
        set("room_id", "xxj");
        set("room_position", "ƽԭС·");
}
