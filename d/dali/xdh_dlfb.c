
#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "С����");
        set("long", @LONG
�������С�������ڴ���ķֶ棬���￴���������ޱȣ�һֻ��
ľ���ϰ��ż������ƵĶľߣ�����������Щ����ͷ����������һ�ɼ�
�㡢����ͺ���������һ���ζ����һ����֪���ǵ�Ʀ��å�ľۼ��ء�
�����ǽ�Ϲ��������ƣ�paizi����
LONG);

        set("objects", ([
               __DIR__"npc/boss-long"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "up" : __DIR__"baiyiminju",
        ]));

        setup();
}
#include <bang_bad.h>

