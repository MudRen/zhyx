// Room: /d/xiangyang/caodi4.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
������������Ĳݵء��ɹű���������������İ���ȫ��
���ˣ����Ｘʮ�ﶼû�����̡�
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"west"  : __DIR__"southgate2",
	]));

        set("objects", ([
                CLASS_D("hu") + "/cheng" : 1,
        ]));

	set("coor/x",-485);
	set("coor/y",-430);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

