// File(/data/room/dgdg/xiaoyuan.c) of dgdg's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ϲ����СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of dgdg");
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
    
        set("room_owner", "������");
        set("room_owner_id", "dgdg");
        set("room_name", "ϲ����");
        set("room_id", "xld");
        set("room_position", "�ݵ�");
}