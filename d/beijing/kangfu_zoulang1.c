#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
����һ��ľ�Ƶ����ȣ�������ǹ⻬����������һ����Ⱦ��������������
���ڴ��߶����ϱ��ǿ����Ĵ�Ժ���������ǿ����Ĵ����ˡ�
LONG );
       set("exits", ([
		"north" : __DIR__"kangfu_dating",
		"south" : __DIR__"kangfu_dayuan",
	]));
	set("objects", ([
		__DIR__"npc/jiading_k" : 1,
		__DIR__"npc/shizhe" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-10);
	set("coor/y",1015);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}