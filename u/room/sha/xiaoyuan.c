// File(/data/room/sha/xiaoyuan.c) of sha's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "ɵ�˼�СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of sha");
	setup();

	set("exits", ([
                "out"    : "/d/gumu/hanshuitan",
	]));

        set("outdoors", "quanzhen");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "ɵ���");
        set("room_owner_id", "sha");
        set("room_name", "ɵ�˼�");
        set("room_id", "sha");
        set("room_position", "��ˮ̶");
}
