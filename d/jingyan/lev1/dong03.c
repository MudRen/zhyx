
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
	set("long", CYN @LONG
����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ�ڡ� 
LONG NOR);
	set("exits", ([
		"east" : __DIR__"dong"+(random(8)+3),
		"south" : __DIR__"dong"+(random(3)+3),
                "west" : __DIR__"dong"+(random(2)+3),
                "north" : __DIR__"dong"+(random(5)+3),
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
