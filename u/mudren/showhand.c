inherit "/inherit/room/showhand";

void create()
{
    set("short", "梭哈三室");
        set("long", @LONG
这里布置得十分豪华气派，当中一张宽大的玉琢方桌，放着一
副崭新的纸牌。两边是宽大的裘皮木椅。一个精干的伙计站在桌旁
负责发牌。墙上挂着简单的规则(ruler)。
LONG
        );
    set("no_learn",1);
    set("no_fight",1);
        set("exits", ([
        "south" : __DIR__"duchang-she",
]));
    set("item_desc",([
        "pai":(:look_pai:),
        "ruler":"\n　　坐下(sit)开始,不想打了就离开(leave)\n"
"　　说话方押(ya)，跟话方跟(gen)，不押(buya)就是认输\n"
"　　最后一牌可以全梭(showhand)，具体请help suoha\n\n",
    ]));

        setup();
}

void init()
{
    object me=this_player();
    if(me->query_temp("duchang_chouma")&&!me->query_temp("duchang_gold"))
        me->delete_temp("duchang_chouma");
    add_action("do_yazhu","ya");
    add_action("do_gen","gen");
    add_action("do_buya","buya");
    add_action("do_sit","sit");
    add_action("do_leave","leave");
    add_action("do_quansuo","showhand");
    add_action("check_chouma","chakan");
}
