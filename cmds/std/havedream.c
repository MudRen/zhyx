// havedream.c 转世后进入梦境的指令
#include <ansi.h>
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
   object ob;
   if ( !me->query("reborn")) return 0;

   if ( !environment(me)->query("sleep_room") )
   {
      write("这里不能睡觉，你怎么做梦呀！\n");
      return 1;
   }

   foreach (ob in deep_inventory(me)) 
   { 
      if (ob->is_character()) 
      {   
         write("你身上带着个大活物怎么做梦呀?\n"); 
         return 1;
      }
   }
   message_vision("\n$N倒头往床上一躺，呼呼大睡起来。\n\n", me);
   message_vision("睡着睡着，$N的身体忽然变得轻飘飘地飞走了。\n\n", me);
   me->set_temp("dream_place", environment(me));
   me->move("/d/zhuanshi/sky/dream");
   message_vision(HIG"一瞬间$N竟飘到了梦境里。\n\n"NOR, me);      
   return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : havedream
 
在你的阿赖耶识被打开后这个指令可以让你随时进入梦境。
要从梦境出来的话可以输入(wake)指令。
 
HELP );
        return 1;
}
