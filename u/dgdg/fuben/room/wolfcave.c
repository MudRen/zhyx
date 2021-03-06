#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", HIW "【远古通道】" NOR);
    set("long", HIW @LONG

                   远古通道

    这里阴森恐怖，不时传来一阵狼嚎之声，令人害怕。四周吹来阵阵
冷风，风中有一股腥味，令你非常的不舒服。
    除了你进来的洞口，在通道尽头还有一个洞穴(dong)，也不知道通
向哪儿。

LONG NOR );

    set("exits", ([
        "out":"/d/huanghe/shulin2",
    ]));
    set("objects", ([
        "/u/dgdg/fuben/npc/dgdg":1,
    ]));

    setup();
    // "/u/dgdg/fuben/room/dgdgcave_b"->foo();
}

void init()
{
    add_action("do_move", "enter");
    add_action("do_act", "hit");
    add_action("do_act", "kill");
}

int do_act(string arg)
{
    object me;
    me = this_player();

    if (!arg || arg == "")
        return 0;

    if (arg != "")
    {
        if (objectp(present("tie chuanjia", environment(me))))
        {
            write(CYN "只听空中一声暴喝：“这位" +
                  RANK_D->query_respect(me) + CYN "，请停步。”\n" NOR);
            return 1;
        }
    }
    return 0;
}

int do_move(string arg)
{
    int n;
    object *inv;
    object me;
    me = this_player();

    if (!arg || arg == "")
        return 0;

    inv = deep_inventory(me);

    for (n = 0; n < sizeof(inv); n++)

    {
        if (!playerp(inv[n]))
            continue;

        else
        {
            message_vision(CYN "\n空中神灵喝道：你个妖人？圣人之地"
                               "可由不得你嚣张！你身上藏着什么!且速速退下\n" NOR,
                           me);

            return 1;
        }
    }

    if (arg == "dong")
    {
        if (me->query_skill("force", 1) > 600 || me->query_skill("dodge", 1) > 600 ||
            me->query_skill("parry", 1) > 600 || me->query_skill("sword", 1) > 600 ||
            me->query_skill("unarmed", 1) > 600 || me->query_skill("martial-cognize", 1) > 600 ||
            me->query("max_qi") > 50000)

        {
            message_vision(CYN "\n空中神灵喝道：你个妖人？圣人之地"
                               "可由不得你嚣张！且速速退下\n" NOR,
                           me);
            return 1;
        }

        return me->move("/u/dgdg/fuben/room/sncave");
    }
}
