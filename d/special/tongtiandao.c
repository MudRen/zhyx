// regiser: tongtiandao 
// by Rcwiz for HERO

#include <ansi.h>

int is_chat_room() { return 1; } 

inherit ROOM;

void create()
{
        set("short", HIW "ͨ�쵺" NOR);
        set("long", @LONG
������һ����������С����������������������������
����PK���ȵ���Ҿ��ᱻ�����ڴ˷�ʡ��ʮ��Сʱ��
    �Ա���һ������(paizi)��
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("exits", ([
                "out"     :     "/d/city/wumiao",
        ]));
        set("item_desc", ([
                "paizi" : HIR "�����˴������ˣ�\n" NOR
        ]));
}

void init()
{        
        add_action("do_notify", ({"eat", "drink", "yun", "exert", 
                                  "perform", "miss", "suicide" }));
}

int do_notify()
{
        write("�ú��ڴ˷�ʡ�ɣ�\n");
        return 1;
}

int valid_leave(object me, string dir)
{
        if (me->query_condition("pk")
           && dir == "out")
             return notify_fail(HIR "\n�ú��ڴ˷�ʡ�ɣ�ʱ������Ȼ������뿪��\n" NOR);

        return ::valid_leave(me, dir);
}

