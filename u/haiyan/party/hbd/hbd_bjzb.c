//hbd_bjzb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "bje"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"�ڰ׵���̳"NOR);
        set("long", @LONG
������Ǻڰ׵������Ƕ���̳�������Ȼ��һ����ȫ���
�ķ��䣡ǽ��Ҳ�쳣�ĵ���֣���Ȼһ���Ǻ�ɫһ���ǰ�ɫ��
����վ��һ���������ˣ��ڰ׷��������壬����Χ�Ļ�������
��һ�𣬸���Ī������Ŀ־�С��������е�̨���Ϸ���һ��
�ڰ����졣�����ǽ�Ϲ���������(paizi)��
LONG);

        set("objects", ([ 
               __DIR__"npc/boss-heibai"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   : "/d/beijing/yancao",
        ]));

        setup();
}
#include <bang_bad.h>

