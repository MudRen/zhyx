#include <room.h>

inherit BUILD_ROOM; 
void create()
{
	set("short", "��������");
	set("long", @LONG
����������������������Ĳݵ�������������ɫ�����ķ��ݡ���
���п���һЩ��֪����С�����к�ġ��Ƶģ������ϵġ������ϡ���Ҷ
�ϵ�¶�����ž�Ө�Ĺ⡣
LONG );
	set("exits", ([		
		"west" : __DIR__"community2",
	]));
	set("no_clean_up", 0);
	set("outdoors", "city");
       set("max_room", 15);
       set("no_fight", 1); 
	setup();
	//replace_program(ROOM);
}

