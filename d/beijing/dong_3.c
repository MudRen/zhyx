#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ض����");
	set("long", @LONG
�����Ǳ����ǵذ��ŵĶ��֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣱���������
�ϱ��ǿ�������������֡�
LONG );
       set("exits", ([
		"north" : __DIR__"wenmiao",
		"south" : __DIR__"wang_9",
		"west" : __DIR__"dong_2",
	]));
	set("objects", ([
		__DIR__"npc/shusheng1" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",10);
	set("coor/y",1060);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

