#include <room.h>

inherit BUILD_ROOM; 
void create()
{
	set("short", "һ������");
	set("long", @LONG
������һ��������������Ĳݵ�������������ɫ�����ķ��ݡ���
���п���һЩ��֪����С�����к�ġ��Ƶģ������ϵġ������ϡ���Ҷ
�ϵ�¶�����ž�Ө�Ĺ⡣
LONG );
	set("exits", ([
		"east" : __DIR__"community2",
		"west" : __DIR__"xiaoyuan",
	]));
	set("no_clean_up", 0);
	set("outdoors", "city");
       set("no_fight", 1); 
       set("max_room", 15);
	setup();
	//replace_program(ROOM);
}

