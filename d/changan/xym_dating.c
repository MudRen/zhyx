
#include <ansi.h>

inherit ROOM;

#define PLACE "ca"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "�����˳����ܶ�");
        set("long", @LONG
�������������ڳ������ܲ�����������ûʲô������װ�Σ�
һ���������ӡ������Ϸ��߸ߵ�������һ�����������֮������
����ͻ͵Ĵ��֡����µ�̫ʦ���϶�����һλ���ϵ��������ӣ�
��ؾ��ǳ��������ɴ󵱼ҡ��������һ�����������˾����Ĵ�
����ǽ�Ϲ���һ�������ƣ�paizi����������������쵽��������
LONG);

        set("objects", ([
               __DIR__"npc/boss-cheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"xym_zb",
        ]));

        setup();
}
#include <bang_good.h>

