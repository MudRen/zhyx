inherit ROOM;
#include <ansi.h>
#include <getconfig.h>
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ڵ�ɽ��·���ϣ�·�����Ҹ���һ����������������
������ɽ��ɽ��������ȥ����������ľ�е�����������Ļ�С�
LONG);
               set("channel_id",HIW"��ؾ���"); 
        set("exits", ([
                "west" : __DIR__"guangchang",
                "east" : __DIR__"shanlu3",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        setup();
}
