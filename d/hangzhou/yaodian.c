// yaodian.c
// Date: Nov.1997 by Venus

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��������");
        set("long", @LONG
����һ����������ҩ�ã���ǽ����һ����ҩ�񡣼��������æ
���������µش�С������ץҩ��ҩ��ǰ����һ�����ӣ�����һλ����
����Ϊ�˰�������������ҽ�����ࡣ
    ��̨�Ϸ��߹�һ��������(paizi).
LONG);
        set("exits", ([
            "west"      : __DIR__"road14",
        ]));
        set("no_beg","1");
        set("objects", ([
            __DIR__"npc/huqingyu" : 1,
        ]));
        set("item_desc", ([
            "paizi" : "������۸���ҩƷ��\n"
        ]));

        set("no_clean_up", 0);
        set("coor/x",200);
	set("coor/y",-410);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
