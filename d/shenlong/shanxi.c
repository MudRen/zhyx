// ɽϪ /d/shenlong/shanxi
// ALN Sep / 97

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ɽϪ");
        set("long", @LONG
��ɽϪ���У�Ϫˮ���ȣ���ľ���£��ĸ��Ŀ�������������ɽ·������
����������һ���޼ʵĴ󺣡�
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "west" : __DIR__"road",
        ]));

        set("cost", 5);

        set("snaketype", ({"shuishe"}));

        setup();
}

#include "/d/shenlong/snakeroom.h"


