
//正气果

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "正气果" NOR, ({ "zhengqi guo", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "这是正气果，吃了会使你侠义之气大增!\n" NOR);
                set("unit", "粒");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10); 
                set("can_cun",1);               
             }
        setup();
}

void init()
{                       
        add_action("do_eat","eat");
}
                
int do_eat( string arg )
{     
         object me;        
         me = this_player();
        

        if ( ! arg || ( arg != "zhengqi guo" && arg != "guo"))
        return notify_fail("你要吃什么?\n"); 
             

         if (me->query("shen") > 1000000)
         {
            tell_object(me, HIC"你的正气已经够多了，再吃也没用了!\n"NOR);
            return 1;
         }
       
         message_vision(HIR "$N一口将正气果吞下了肚子，顿时一副凛然正气袭上周身!\n" NOR, me);
         tell_object(me, HIC"你的正气增加了!\n"NOR);

         me->add("shen", 2000 + random(500));

         destruct(this_object());
         return 1;
}
                
int query_autoload() 
{ return 1; }


        
