// Room: /d/mingjiao/shanmen.c
// Date: Java 97/04/3

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "����ɽ��");
    set("long", @LONG
һ���޴����Ȼʯ�ź������Ƭɽ��֮�䣬ʯ�����Ϸ�����
��������������֣������̡����ּ���Щ���䣬����ȥ�����Զ��
��λ��ʮ����Ĵ��ֳָֽ�����ɽ�����ࡣ
LONG );
    set("exits", ([
        "westup" : __DIR__"shanlu1",
        "east" : __DIR__"tomen1",
    ]));
    set("outdoors", "mingjiao");
    set("objects",([
        __DIR__"npc/jieyinshi" : 1,
        "/kungfu/class/mingjiao/lengqian" : 1,
    ]));

    setup();
}


