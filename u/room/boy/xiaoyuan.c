// File(/data/room/boy/xiaoyuan.c) of boy's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��Ȼ��СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of boy");
	setup();

	set("exits", ([
                "out"    : "/d/huanghe/caodi1",
	]));

        set("outdoors", "huanghe");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "��������");
        set("room_owner_id", "boy");
        set("room_name", "��Ȼ��");
        set("room_id", "you");
        set("room_position", "�ݵ�");
}
