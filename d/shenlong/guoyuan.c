// /d/shenlong/guoyuan.c
// ALN Sep / 97

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
����һƬ��԰���ֵ���һЩˮ������ƻ������ͷ��ɽ�ꡢ���ӡ����ӡ�÷
�ӵȣ��е��ѵ����ջ�ʱ�ڣ�֦ͷ�ѱ���ʵѹ�������������ģ���һ��֦ͷ
һ��һ���ģ����˿���ֱ����ˮ�����桢�����ƺ�����ũ�������ɽ�𣬶�
����ֱͨ�����̵ĳ�����
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "west" : __DIR__"chufang",
        ]));
        set("objects", ([
            "/d/shenlong/obj/apple" : 2 + random(8),
        ]));
        set("cost", 3);
        set("snaketype", ({"yinhuan"}));
        setup();
}

#include "/d/shenlong/snakeroom.h";

