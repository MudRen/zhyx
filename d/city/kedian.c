#include <room.h>
#include <ansi.h>

inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
    set("short", "有间客栈");
    set("long",
WHT "\n        ※※※※※※※※※※※※※※※※※\n"
                              "        ※          有间客栈            ※\n"
                              "        ※   " NOR + HIW "地下室客店，免费提供住宿。" NOR + WHT " ※\n"
                              "        ※        楼上为巫师办公处      ※\n"
                              "        ※※※※※※※※※※※※※※※※※\n\n" NOR,
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
