// File(/data/room/keep/houyuan.c) of keep's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "��Ժ");
	set ("long", @LONG
���Ƿ���С���ĺ�Ժ������һ����ɽ����Ȼ�������ǳ���ΰ����
��һˮ�أ���ɽ���ߣ���Ȼ��Ϣ��������������֮���������ǳ�����
LONG );

	set("exits", ([
                "south" : __DIR__"zhongting",
                "north" : __DIR__"huayuan",
                "east"  : __DIR__"lianwu",
                "west"  : __DIR__"chufang",
	]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "���ҵ�");
        set("room_name", "����С��");
        set("room_id", "fyxz");
        set("room_owner_id", "keep");
        set("room_position", "�ϴ��");
}
