
#include <ansi.h>

inherit ROOM;

#define PLACE "cd"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "�����ŷ�̳");
        set("long", @LONG
�����Ǻڵ���֯�����ŵĳɶ���̳������һ����ɭ�ֲ���
���䣬��������Ϊ�������ֿ��£������������Ե�����������
����������̬���죬���˸о��·�����������һ�㡣ǽ��
���������ŵ������ƣ�paizi����
LONG);

        set("objects", ([
               __DIR__"npc/boss-leng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"qingyanggong",
        ]));

        setup();
}
#include <bang_bad.h>

