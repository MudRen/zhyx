
#include <ansi.h>

inherit ROOM;

#define PLACE "sz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "��������̳");
        set("long", @LONG
�����������ŵ��ܲ����������䶼��ɭɭ�ģ�������һ��
����裬���緢�������Ļ��档���˾��ò���������ǰ̨�ڷ�
��һ���ν���������������������ӳ��һ��ģ�������������
����������Ī�������ɲ�ˡ�һ���ǽ�Ϲ��������ƣ�paizi����
LONG);

        set("objects", ([
               __DIR__"npc/boss-yu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"hutong3",
        ]));

        setup();
}
#include <bang_bad.h>

