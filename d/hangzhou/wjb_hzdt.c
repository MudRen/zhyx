
#include <ansi.h>

inherit ROOM;

#define PLACE "hz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "�޼��ﺼ�ݷֶ�");
        set("long", @LONG
�������޼������ں��ݵķֶ棬����װ�εļ�Ϊ�������棬
һ���������������һ���޴��ɽˮ���续�����������Ǻ�����
���ϵ����������ĵ�̺���ߣ�������������������Σ�������
�ﾭ������Щ�޼���Ĵ��¡�һ�����ʲ����������ˣ�������̫
ʦ���ϡ���ؾ����޼��ﺼ�ݷֶ����򽣳�������ˡ������ǽ
�Ϲ��������ƣ�paizi���� 
LONG);

        set("objects", ([
               __DIR__"npc/boss-wan"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "east" : __DIR__"wjb_hzfb",
        ]));

        setup();
}
#include <bang_good.h>

