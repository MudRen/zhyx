#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߲��Թ�");
        set("long", @LONG
������������ĳ�������ǰ�����������������Թ�֮
�ڲ����㼣ָ�����㲻֪��Ҫ������·�ߡ�����ϸ����������
���׺�ǰ������·�϶��е������㼣�����ƺ���ʧ�˷�����
ûͷ��Ӭ�㵽���Ҵ���
LONG);
        set("exits", ([
                "east" : __DIR__"shulin8",
                "west" : __DIR__"shulin" + (random(10) + 2),
                "south" : __DIR__"shulin" + (random(10) + 2),
                "north" : __DIR__"shulin6",
        ]));

        set("outdoors", "gaochang");
        setup();
        //replace_program(ROOM);
}