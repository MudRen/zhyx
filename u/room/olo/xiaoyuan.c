// File(/data/room/olo/xiaoyuan.c) of olo's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "̫�Ӹ�СԺ");
	set ("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ���
�Ƿǳ���ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо���
Ժ��������Լ��ɽ���ٲ���Ժ�ӵı�����һ��ľ�š� 
LONG );

        set("room_key", "1 of olo");
	setup();

	set("exits", ([
                "out"    : "/d/huashan/shanhongpb",
	]));

        set("outdoors", "huashan");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "��ʮ");
        set("room_name", "̫�Ӹ�");
        set("room_OWNER_ID", "olo");
        set("room_id", "ouo");
        set("room_position", "ɽ���ٲ�");
}
