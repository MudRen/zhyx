//hbd_xyfb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"�ڰ׵�������̳"NOR);
        set("long", @LONG
������Ǻڰ���֯�ڰ׵���������̳�ˣ�ǽ�������صĺ�
����ɫ������ȴ���Ż����ĵ�̺�����е�̫ʦ���ϵİ׻�ƤҲ
��ʾ����������˱ض���Ľ�ٻ�����ǽ�Ϲ��Ÿ����ӣ�paizi����
LONG);

        set("objects", ([ 
               __DIR__"npc/hbd_jiabj"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   :  __DIR__"hutong2",
        ]));

        setup();
}
#include <bang_bad.h>

