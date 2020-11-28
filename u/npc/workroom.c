// Room of wizard that haven't modify own workroom
// Updated by Lonely

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
          set("short", HIM"�����޻ڵ���Դ�ɾ���"NOR);
        set("long",HIW @LONG
�������ڽ�����ʦ���޻ڵ�ס��������Ѿ������޻ڰ�
���ݺ����¾�ס�ˡ�һȺ��ɽ֮���Ͽ�ȴ��̵���������ӵ
�ű̲������ĳ����������������ӳ�����������������
�䡣����ǰ��һƬ���֣��ۺ�ɫ���һ��ļ����š�
LONG NOR);

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
                "down"  : "/d/city/kedian",
        ]));
        set("objects", ([
                "/kungfu/class/sky/npc/hua" : 1,
                "/kungfu/class/sky/npc/kou" : 1,
                "/kungfu/class/sky/npc/xu" : 1,
        ]));
        set("valid_startroom", 1);
        set("no_fight",1);
        set("sleep_room", "1");
        set("no_clean_up", 0);
        setup();
     //    "/clone/board/jing_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && !wizardp(me))
                return notify_fail("����ֻ����ʦ���ܽ�ȥ��\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_all_action();
        add_action("do_action", "");
        add_action("do_here", "come");
        add_action("do_sanweapon", "sanweapon");
}

int do_action(string arg)
{
        object me, *ob, ob1;
        int i;
        me = this_player();
        ob = all_inventory(environment(me));

        if (this_player()->query("id") != "jing")
        {
                string action = query_verb();

                switch (action)
                {
                case "smash":
                        write(HIW "�����Ǿ��޻ڵķ��䣬��������\n" NOR);
                        return 1;
                }
        }
        if (arg != "")
        {
                for (i = 0; i < sizeof(ob); i++)
                {
                        ob1 = query_snoop(ob[i]);
                        if (!living(ob[i]))
                                continue;
                        if (objectp(ob1))
                        {
                                snoop(ob1);
                                tell_object(ob[i], HIW + ob1->name(1) + "�������������ֹ��\n" NOR);
                        }
                }
        }
        return 0;
}

int do_here(string arg)
{
        object me, *user;

        user = users();
        me = this_player();

        if (me->query("id") != "jing" || arg != "here")
                return notify_fail("What are you doing ?");

        foreach (object player in user)
        {
                if (wizardp(player))
                        player->move("/u/jing/workroom.c");
        }
        return 1;
}

int do_sanweapon(string arg)
{
        object me = this_player();
        object ob;
        if (!arg || !objectp(ob = present(arg, environment(me))))
                return 0;
        if (!ob->is_item_make())
                return 0;
        ob->set("magic/imbue_ok", 1);
        return 1;
}
