#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ʹ�ƫ��");
        set("long", @LONG
��������Ͻ��ǵ����ŵĴ�Ѱ�������ǵ������������ģ�������Բ�
������;������������ǸϿ��뿪Ϊ�á�
LONG NOR);
        set("exits", ([
                "east" : __DIR__"hg",
        ]));
        set("objects", ([
                __DIR__"npc/yuqian1" : 2,
        ]));
        set("no_fight",1);
        setup();
}
