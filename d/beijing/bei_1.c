#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
�����Ǳ����ǵ���������֣������Ĵ�����ϱ��������졣�ֵ��ϵ�����
����������о������������ٱ����������Լ�С��С����ߺ�������ϣ�������
�����У��������֡����ߵĽֵ�ͨ�����š�
LONG );
       set("exits", ([
		"east" : __DIR__"bei_2",
		"west" : __DIR__"ximenkou",
		"north" : __DIR__"bei_3",
		"south" : __DIR__"xi_1",
	]));
	set("objects", ([
		__DIR__"npc/youren" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-50);
	set("coor/y",1020);
        set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

