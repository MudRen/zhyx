inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","���ι���");
	set("long", @LONG
������һ����լ��ǰ����լ�Ĵ��Ž����ر��ţ����Ϲ���һ����ң�����
д�š����ι������ĸ����֣���Ȼ��¹������ͬ�ǹ����������Ǵ�С����ͷȴ
����ͬ�������Ҷ����ǡ����ι����������Ǻ��֣�һ��Ҳ�����ۡ�
LONG );
	set("exits", ([
		"north" : __DIR__"fu_2",
		"south" : __DIR__"hai_dayuan",
	]));

	set("coor/x",-10);
	set("coor/y",970);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
