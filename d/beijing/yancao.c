#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�̲ݵ�");
	set("long", @LONG
�������������������������˵����ѵ���Ʒ�����������ǳɰٳ�ǧ����
������ȥ���������������е�����ķ�ʽ�����̡�������Զ��ס�������к���
���ģ�����������ϰ屻��������ͷ�ϡ������ĲƵ������Ǳ�������ġ�
LONG );
       set("exits", ([
		"north" : __DIR__"caroad_e2",
	]));
	set("objects", ([
		__DIR__"npc/old2" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",20);
	set("coor/y",990);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

