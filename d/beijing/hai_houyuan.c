inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","��Ժ");
	set("long", @LONG
�����Ǻ��ι�����������һ��С��԰�����ҵ����Ÿ��ֻ��ݣ���������
�������Ӳ��Ѿ����úܸ��ˡ�һЩ�ʻ������ڲݴ��У������㲻�ϵ�Ʈ����
LONG );
	set("exits", ([
		"north" : __DIR__"hai_dating",
	]));

	set("coor/x",-10);
	set("coor/y",940);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}