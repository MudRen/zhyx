// shuyuan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "�����Ժ");
        set("long", @LONG
��Ժ������һ�ҡ������Ժ������Ժ��������λ���ߣ���������
��ʫ���ԡ��������Ե�����������ֽ�ͱ�ī��
LONG);
        set("exits", ([
            "west"      : __DIR__"road12",
        ]));
        set("no_clean_up", 0);
        set("coor/x",200);
	set("coor/y",-390);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
