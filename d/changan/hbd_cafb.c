//hbd_cafb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "ca"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"�ڰ׵�������̳"NOR);
        set("long", @LONG
������Ǻڰ���֯�ڰ׵��ĳ�����̳�ˡ�ǽ�������صĺ�
����ɫ���������е�̨���ϰ���һ�ѽ�һ�ѵ������Կ����˴�
�ķ�̳���ض��Ǹ�������ѧ֮�ˡ�ǽ�Ϲ���һ�����ӣ�paizi����
LONG);

        set("objects", ([ 
               __DIR__"npc/hbd_chengwu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   :  __DIR__"miao",
        ]));

        setup();
}
#include <bang_bad.h>

