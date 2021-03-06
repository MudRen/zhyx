// 黑店: /clone/heidian/dali_heidian.c
// 黑店程序由smallfish编写

inherit ROOM;
inherit F_HEIDIAN;

void create()
{
    set("short", "烽火流星");
    set("long", @LONG
这里是大宗师流星的店铺, 里面摆满了一些希奇古怪的玩意儿,
只要来大理没有不来这看看,也许能找到自己中意的东西, 平时流星
也不在, 只有一个小女孩在看店.
LONG);

    set("no_fight", 1);
    set("exits", ([/* sizeof() == 1 */
        "east":"/d/dali/center",
    ]));
    set("no_steal", 1);
    set("shop_type", 0);
    set("objects", ([/* sizeof() == 1 */
        __DIR__ "dali_huoji":1,
    ]));
    set("owner", "VOID_HEIDIAN");
    set("no_beg", 1);
    set("no_clean_up", 0);

    setup();
}

init()
{
    if (query("owner") == this_player()->query("id"))
    {
        add_action("do_short", "short");
        add_action("do_long", "long");
    }
}
