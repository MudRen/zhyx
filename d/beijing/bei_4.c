#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
�����Ǳ����ǵ���������֣������Ĵ�����ϱ��������졣�ֵ��ϵ�����
����������о������������ٱ����������Լ�С��С����ߺ�������ϣ�������
�����У��������֡�����ͨ��������֡�
LONG );
       set("exits", ([
		"west" : __DIR__"bei_3",
		"north" : __DIR__"di_1",
		"south" : __DIR__"bei_2",
	]));
	set("objects", ([
		__DIR__"npc/youren" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-30);
	set("coor/y",1030);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

