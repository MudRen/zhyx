#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���㹬������������߳����ɣ�ΡȻ��
������������֮�ϣ���������ƫ����������
Ϊ�ͣ���߳������������������࣬����һ��
ʮ�ɵĳ�������������������һֻ������
Ұ�ޣ������ں�ҹ�ɽ����������¥��
LONG
        );

              set("no_stab", 1); 
        set("outdoors", "qianhuigu");
        set("exits", ([ /* sizeof() == 3 */
		"south" : __DIR__"migong1",
		"east" : __DIR__"migong3",
		"west" : __DIR__"migong4",
		"down" : __DIR__"migong5",
        ]));

        setup();
        replace_program(ROOM);
}

