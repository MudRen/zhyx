#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"ʯ��"NOR);
	set("long", @LONG
����һ��������ʯ������Χ���Ǽ�Ӳ��ʯ��,ǰ���������ϵĽ��ݡ�
LONG CYN);
	set("exits", ([
		"east" : __DIR__"dong24",
		"west" : __DIR__"dong25",
                "up" : "/d/migong/lev2/dong20",
                	]));
                set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
