// File(/data/room/xme/xiaoyuan.c) of xme's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ħ��СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of xme");
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
    
        set("room_owner", "��֮��");
        set("room_owner_id", "xme");
        set("room_name", "ħ��");
        set("room_id", "hell");
        set("room_position", "ƽԭС·");
}
