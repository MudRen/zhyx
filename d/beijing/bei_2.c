#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
�����Ǳ����ǵ���������֣������Ĵ�����ϱ��������졣�ֵ��ϵ�����
����������о������������ٱ����������Լ�С��С����ߺ�������ϣ�������
�����У��������֡������ߵ�ͨ�����ţ�������һ�������ûʵĽ������Ŷ���
����һ�����ң�д�š������������ĸ����֡�
LONG );
       set("exits", ([
		"east" : __DIR__"kangfu_men",
		"west" : __DIR__"bei_1",
		"north" : __DIR__"bei_4",
		"south" : __DIR__"xi_2",
	]));
	set("outdoors", "beijing");
	set("coor/x",-30);
	set("coor/y",1020);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

