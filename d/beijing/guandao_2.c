#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
������һ����������Ĵ�ٵ��ϡ���ʱ��������������߷ɳ۶�������
��һ·��������·��������������������֡�������Զ�����Ǿ�����������ʤ
ʮ�����ꡣ
LONG );
       set("exits", ([
		"north" : __DIR__"huangling",
		"south" : __DIR__"guandao_1",
	]));
	set("outdoors", "beijing");
	set("coor/x",-41);
	set("coor/y",1051);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

