inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "��������");
	set("long", @LONG
������Ǿ��ǵ�����������������Ĵ��š����ﾯ�����ϣ���ʱ�д�����
���������ٱ���������������������ȥ�����������������������̫�ࡣ����
���Ե������ٱ��������ƻ��Ķ����㿴������㲻�������Ļ�����û��ǸϿ�
�뿪�ĺá�
LONG NOR);
	set("exits", ([
		"south" : __DIR__"xichang",
		"north" : __DIR__"di_2",
	]));
	set("objects", ([
		__DIR__"npc/bing3" : 2,
	]));
	set("coor/x",-20);
	set("coor/y",1039);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

