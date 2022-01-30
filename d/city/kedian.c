#include <room.h>
#include <ansi.h>

inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
    set("short", "�м��ջ");
    set("long",
WHT "\n        ����������������������������������\n"
                              "        ��          �м��ջ            ��\n"
                              "        ��   " NOR + HIW "�����ҿ͵꣬����ṩס�ޡ�" NOR + WHT " ��\n"
                              "        ��        ¥��Ϊ��ʦ�칫��      ��\n"
                              "        ����������������������������������\n\n" NOR,
);
    set("no_fight", 1);
    set("valid_startroom", 1);
    set("no_sleep_room",1);
    set("objects", ([
        __DIR__"npc/xiaoer" : 1,
        "/u/kasumi/npc/kasumi" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"beidajie1",
        "up"   : "/d/wizard/advice",
        "down" : __DIR__"kedian2",
        "south": __DIR__"liaotian",
    ]));

    setup();
    "/clone/board/kedian_b"->foo();
    "/adm/npc/beichou"->come_here();
}

void init()
{
    add_all_action();
}
