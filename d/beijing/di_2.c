#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����Ǳ����ǵذ��ŵ����֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣱����ǵذ���
���ֵĹ㳡���ϱ߾������ϣ���ʱ�йٱ�����������ԭ��������Ǿ��ǵ�����
���������Ĵ������ڵء�
LONG );
       set("exits", ([
		"north" : __DIR__"di_xigc",
		"west" : __DIR__"di_1",
		"south" : __DIR__"xichang_men",
	]));
	set("objects", ([
		__DIR__"npc/bing3" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x",-20);
	set("coor/y",1040);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

