// File(/data/room/rong/houyuan.c) of rong's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "��Ժ");
	set ("long", @LONG
����ܽ�ؾӵĺ�Ժ������һ����ɽ����Ȼ�������ǳ���ΰ������
һˮ�أ���ɽ���ߣ���Ȼ��Ϣ��������������֮���������ǳ����� 
LONG );

	set("exits", ([
                "south" : __DIR__"zhongting",
                "north" : __DIR__"huayuan",
                "east"  : __DIR__"lianwu",
                "west"  : __DIR__"chufang",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "ˮ�ض�");
        set("room_name", "ܽ�ؾ�");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "�Ϻ����");
}
