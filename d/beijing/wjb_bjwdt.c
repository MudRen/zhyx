
#include <ansi.h>

inherit ROOM;

#define PLACE "bjw"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "�޼��ﱱ�����Ƿֶ�");
        set("long", @LONG
�������޼������ڱ����ķֶ棬����װ�εļ�Ϊ�������棬
һ���������������һ���޴��ɽˮ���续�����������Ǻ�����
���ϵ����������ĵ�̺���ߣ�������������������Σ�������
�ﾭ������Щ�޼���Ĵ��¡������ǽ�Ϲ��������ƣ�paizi���� 
LONG);

        set("objects", ([
               __DIR__"npc/boss-zhong"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "west" : __DIR__"wjb_bjwfb",
        ]));

        setup();
}
#include <bang_good.h>

