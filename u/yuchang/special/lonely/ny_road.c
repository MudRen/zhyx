// ŦԼ��

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "ŦԼ����С��");
	set("long", @LONG
������ŦԼ�����һ��С��������ͨ��ŦԼ�����ġ�
LONG );
	set("exits", ([		
		"west"        : __DIR__"road2",
              "east"        : __DIR__"newyork",
	]));
	setup();	
}

