#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���ı����");
	set("long", @LONG
���������ı���ֵľ�ͷ����ʯ��������൱�������ֵ��ϵ�����������
������������Ϣ�����߽ӵ�����֣�ת����ͨ�������ϴ�ֽӾ��ǵ�������
��֡�
LONG );
       set("exits", ([
		"east" : __DIR__"di_4",
		"south" : __DIR__"shi_2",
	]));
	set("outdoors", "beijing");
	set("coor/x",-40);
	set("coor/y",1060);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

