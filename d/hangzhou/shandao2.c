// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "ɽ��");
	set("long", @LONG
���Ѷ��ϵ�ɽ���������ͣ��ߴ����ľ��������ԼԼ¶�������Ʈ���ķ�
����Ұ������������ŨŨ�����ں��������ʱ��������������ˮ�������˴�
�̵�ɽ�ȣ�ȴ���Ҳ���Ϫ������Ӱ��
LONG );
	set("exits", ([
		"north" : __DIR__"yuanyuan-tai",
		"south" : __DIR__"shandao1",
	]));
	
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
