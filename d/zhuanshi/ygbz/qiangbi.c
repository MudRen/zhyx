// yuchang /2002/3/15/
#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "钢壁");
        set("long", @LONG 
这是用钢铸造的钢壁,探察不出他的厚度,但是估计不底,
你在这里用吸壁功吸着是很费内力的!还是快点(jump)跳下
去吧。
LONG);
        setup();
}

void init()
{
    object me;
    me = this_player();

    if (userp(me))
   {
       remove_call_out("do_suck");
       call_out("do_suck", 1, me);
   }
    
   add_action("do_jump", "jump"); 
}

int do_jump(string arg)
{
    object me; 
    me = this_player();

    if ( !arg || arg != "up" ) 
    {
       write("你是要往上(up)跳吗!\n");
       return 1;
    }
    if (me->query_skill("dodge",1) < 600)
    {       
       write("你拼命忘上跳,但是因为轻功不够失败了!\n\n");
       write(HIR"看来你只有挂在这里等死了！\n\n"NOR);
       return 1;
     } 

     write(HIY"你纵身往上一跃，跳回到了密道!\n\n");

     write(BLINK HIR"你突然发现原来制钮的右边还有个制钮!\n\n"NOR);

     me->set_temp("tongguo",1);
     me->move(__DIR__"tongdao5");
     return 1;
}

    
void do_suck(object me)
{
     if (!me) return;
     if (environment(me) != this_object()) return;  
  
     if ( me->query("neili") > 0 )
     {
       tell_object(me, HIR"你感到身上的内力在慢慢消耗!\n"NOR);
       me->add("neili", - (500 + random(500))); 
     }

     if (me->query("neili") <= 1500) 
    {    
        tell_object(me, BLINK HIB"你的内力已经快耗尽了，"
                        "再不想想办法就危险了!\n"NOR); 
    }  

    if ( me->query("neili") > 0 )
    {
       remove_call_out("do_suck");
       call_out("do_suck", 2, me);
    }
    else
   {
       me->set_temp("die_reason", "跌下无底洞摔死了");
       me->die();    
   }
}