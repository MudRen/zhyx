// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "ɽ��");
	set("long", @LONG
����������һ�����ѵ�ɽ���ϣ����߷�ï����ľɢ�������������˵���Ϣ��Ϫ
���ڹ��������ʣ�ˮ��������á�����������ɽ����ɫ����Ӱ���ף���ӳ�ɻ���
LONG );
	set("exits", ([
		"north" : __DIR__"shandao2",
		"west" : __DIR__"wenxin-quan",
		"south" : __DIR__"quanbian-xiaojing",
	]));
	
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
