
//巧克力(加10万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "巧克力" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "好吃的巧克力,每个增加十万点经验和潜能。\n" NOR);
                set("unit", "个");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);
             }
        setup();
}

void init()
{
     add_action("do_eat","eat");
}

int do_eat( string arg )
{       object me;
        me = this_player();

        if ( ! arg || (arg != "qiao keli" &&
             arg != "chocolate") )
        return 0;

        if (me->query("gift2015/newyear/eat"))
        {
            me->delete ("gift2015");
            me->set("reward/gift/choco/eat", 1);
            write(HIR "巧克力偿一次就够了，这里毕竟是武侠游戏!\n" NOR);
            return 1;
        }

        if (me->query("reward/gift/choco/eat"))
        {
            write(HIR"巧克力偿一次就够了，这里毕竟是武侠游戏!\n"NOR);
            return 1;
        }

        message_vision(HIW "$N" HIW "将巧克力一口吞了。\n" NOR, me);
        me->add("combat_exp", 100000);
        me->add("potential",100000);
	    if (me->can_improve_skill("force"))
            me->improve_skill("force", 1500000);
			  if (me->can_improve_skill("dodge"))
            me->improve_skill("dodge", 1500000);
			  if (me->can_improve_skill("parry"))
            me->improve_skill("parry", 1500000);


        tell_object(me, HIG"恭喜你增加了十万点经验和潜能。"
                    "祝你游戏快乐！\n"NOR);
        me->set("reward/gift/choco/eat", 1);
        destruct(this_object());
        return 1;
}
