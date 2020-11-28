// room: well1.c
// BY yuchang

inherit ROOM;
#include <ansi.h>
#define QUAN "/d/zhuanshi/obj/quan"
int do_use(string arg);
int do_search(string arg);

void create()
{
        set("short", "����");
        set("long", @LONG
�����ڸ߲������һ�����ң�ʲôҲ�����塣
LONG);
        set("exits", ([
                "out":__DIR__ "mishi2",
        ]));
        set("no_clean_up", 0);
        set("item_desc", (["hole":"һ����֪��ǳ��ʯ������֪�ò�����һ�ѿ���\n"]));
        set("count", 1);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_search", "search");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if (!arg || arg == "")
                return 0;
        if (!present("fire", me))
                return 0;
        if (arg == "fire")
        {
                message_vision("$N��ȼ�˻��ۣ�����ǽ������һС��(hole)���ƺ���ʲô���������档\n", me);
                me->set_temp("marks/fire", 1);
                return 1;
        }
}

int do_search(string arg)
{
        object me, ob;
        object quan;
        object none;
        me = this_player();

        if (!me->query_temp("marks/fire"))
                return 0;
        if (!arg || (arg != "hole" && arg != "С��"))
                return notify_fail("��Ҫ�����\n");
        if (query("count") < 1)
        {
                return notify_fail("������ʲôҲû���ˡ�\n");
        }
        if (me->query("cor") < 25)
                return notify_fail("��������֣���Ȼ�е㺦�£������뻹�����ˡ�\n");
        add("count", -1);
        quan = new (QUAN);
        if (quan->violate_unique())
        {
                destruct(quan);
                quan = none;
        }
        if (random(4) > 0 && quan)
        {
                message_vision("$N���������������������Ȧ����\n", me);
                message("channel:chat", MAG "���߲��Թ���ĳ�ˣ�" + me->query("name") + "�õ����Ȧ����\n" NOR, users());
                quan->move(me);

                return 1;
        }
}
