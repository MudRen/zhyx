#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
������һ����������Ĵ�ٵ��ϡ���ʱ���������������
�߷ɳ۶���������һ·��������·��������������������֡���
LONG );
       set("exits", ([
		"north" : __DIR__"xiaodao1",
		"south" : __DIR__"guandao_1",
	]));
	set("outdoors", "xiangyang");
	set("coor/x",-540);
	set("coor/y",-390);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
