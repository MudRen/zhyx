// Room: /d/gaibang/underdl.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ͽֱ�");
	set("long", @LONG
���Ǵ�����д�ͽֱ��ϵĴ������������������õģ������˸���
�������ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ����
���˾��ȵ��������Ȼ���˼���ľ�ˣ��������浽�������������ӡ��
���ϻ��������������һЩ���ȹ�ͷ��
LONG );
	set("exits", ([
		"out"       : "/d/dali/dahejieeast",
		"northeast" : __DIR__"dlandao2",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 4,
		"/d/city/obj/bone"  : 2,
	]));
	setup();
	replace_program(ROOM);
}

