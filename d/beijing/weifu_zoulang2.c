#include <room.h>
inherit ROOM;

void create()
{
	set("short", "Τ������");
	set("long", @LONG
����һ��ľ�Ƶ����ȣ�������ǹ⻬����������һ����Ⱦ������Τ������
���ڴ��߶����ϱ��Ǹ��޴�Ļ�԰�����߾���Τ���Ĵ�����
LONG );
       set("exits", ([
		"north" : __DIR__"weifu_dating",
		"south" : __DIR__"weifu_dayuan",
	]));

	set("outdoors", "beijing");
	set("coor/x",1);
	set("coor/y",1030);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}