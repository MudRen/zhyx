#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������ͬ");
	set("long", @LONG
������������ͬ�ĺ�ͬ�ڣ��������������ϱ����۵�������ȥ������ʱ
�֣���ͬ�ڲ�Զ�����ߴ������죬���Ǿ�ס�ż����˼ҡ�ֻ�������������
��������ߺ�����໥���壬������ǹᴩ���ǵĳ�����֡�
LONG );
       set("exits", ([
		"north" : __DIR__"caroad_w1",
		"south" : __DIR__"yangliu2",
		"west" : __DIR__"minju_y",
	]));
	set("objects", ([
		__DIR__"npc/old1" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-30);
	set("coor/y",990);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

