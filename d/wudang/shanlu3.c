#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ڵ�ɽ��·���ϣ�·�����Ҹ���һ����������������
������ɽ��ɽ��������ȥ����������ľ�е�����������Ļ�С�
LONG);
          set("channel_id",HIW"��ؾ���");
        set("exits", ([
                "west" : __DIR__"shanlu2",
                "southup" : __DIR__"shanlu4",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        setup();
}
