// 转世神器之 魔戒
// Create by yuchang

#include <ansi.h>

#include <armor.h> 
inherit HANDS; 

void create()
{
        set_name(HIB "魔戒" NOR, ({ "mo jie", "mojie", "ring" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "枚");
                set("long", HIG "这是一枚传说中的戒指，周身泛着眩目的光华，据\n"
                                "说是天神浪翻云为了打通天地交界处所用。可用之\n"
                                "来破碎虚空(crack)，进入天界。\n" NOR);
                set("material", "steel");
                set("wear_msg", HIB "$N" HIB "将魔戒戴在中指，顿时一"
                                    "道蓝光闪过。\n" NOR);
                set("remove_msg",HIG "$N" HIG"将魔戒从手指上取下来。\n" NOR);
                set("value",100000);
                set("no_sell", 1);
                set("armor_prop/finger", 10);               
                set("armor_prop/unarmed", 10);  
                set("armor_prop/claw", 10);  
        }
        setup();
}

void init()
{   
     object me;        
     me = this_player();
        
     if ( !query("owner") &&    
          objectp(present("mo jie", me)))
     set("owner", me->query("id"));

     add_action("do_crack", "crack");  
    
  
}

int do_crack(string arg)
{
        object me;        
        me = this_player();
        
        if(! objectp(present("mo jie", me))) return 0;

        if (query("owner") != me->query("id") )
            return notify_fail("这不是你的魔戒，你不能使用！\n");

        if (me->is_fighting() || me->is_busy() ||
            me->query("doing") )
            return notify_fail("你正忙呢！\n");
                 
        message_sort(HIG"\n$N" HIG "手中的魔戒发出耀眼蓝光，"
                     "刹那间天空中露出一道裂痕，魔戒化做一道奇异的光芒将$N"
                     HIG"卷进虚空之中。\n\n" NOR, me);
                
        me->move("/d/zhuanshi/sky/sky1");
        return 1;
}

string query_autoload()
{
       if (! query("owner") ) return 0;
       return query("owner");
}

void autoload(string owner)
{
    if ( ! owner)   
     {        
        destruct(this_object());
        return;
     }
     set("owner", owner);
}

