
//巧克力(加20万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "巧克力" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "巧克力礼物,每个加40万经验和潜能。\n" NOR);
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
        


        message_vision(HIW "$N" HIW "将巧克力一口吞了。\n" NOR, me);
        me->add("combat_exp", 400000);
        me->add("potential",400000);
	   	    

        tell_object(me, HIG"恭喜你增加了四十万点经验和潜能。"
                    "希望你再接再厉！\n"NOR);

        destruct(this_object());
        return 1;    
}

