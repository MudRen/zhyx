#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������Ժ");
	set("long", @LONG
���ǿ����������Ŷ��ߵ�һ�������Ĵ�Ժ��Ժ�ڴ�ɨ�÷ǳ��ɾ�����Χ��
�����˸��໨�ݣ�����������˴������У�������һ��ľ�����ȣ�ͨ��������
������
LONG );
       set("exits", ([
		"west" : __DIR__"kangfu_men",
		"north" : __DIR__"kangfu_zoulang1",
	]));
	set("objects", ([
		__DIR__"npc/jiading_k" : 2,
		__DIR__"npc/yuanding" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-10);
	set("coor/y",1020);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}