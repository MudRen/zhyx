// Room: /d/xiangyang/westgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "�׻�����");
	set("long", 
"�����������ǵ������ţ�ֻ�������Ϸ����������֡�"HIW"

                      �׻���
\n"NOR
"�������ɹ��Ŵ��ַ������ǣ�����������൱���ܣ�һЩ�ٱ�
�������̲�Ҫ�������ǵ��ˡ������Ǻܴ�Ĳݵء�\n"
 );
        set("outdoors", "xiangyang");

	set("exits", ([
		"east"  : __DIR__"westgate1",
                "west"  : __DIR__"guandao_1",
	]));
	set("objects", ([
		"/d/xiangyang/npc/pi"   : 1,
		"/d/xiangyang/npc/bing" : 2,
	]));
	set("coor/x",-530);
	set("coor/y",-400);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

