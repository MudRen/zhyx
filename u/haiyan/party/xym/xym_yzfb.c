//xym_yzfb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "yz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "���������ݷֶ�");
        set("long", @LONG
�����������������ݵķֶ档�ֶ����֣�ƻ��˳��������µ�һ
Ա�ͽ�������������ڷ����ǽ����һ������(paizi)������������
����ң�����������ѡ������ȥ��ɡ�
LONG);

        set("objects", ([
               __DIR__"xym_zheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"xym_yzdamen",
        ]));

        setup();
}
#include <bang_good.h>

