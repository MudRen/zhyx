// File(/data/room/super/houyuan.c) of super's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "��Ժ");
	set ("long", @LONG
������Ʒ�õĺ�Ժ������һ����ɽ����Ȼ�������ǳ���ΰ������
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

        set("room_owner", "����");
        set("room_name", "��Ʒ��");
        set("room_id", "room");
        set("room_owner_id", "super");
        set("room_position", "ƽԭС·");
}
