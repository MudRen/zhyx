// mingsi.c

#include <skill.h>

inherit F_CLEAN_UP;

int mingsi(object me);
int halt_mingsi(object me);

void create() { seteuid(getuid()); }

int main(object me)
{	
	object where;        

	seteuid(getuid());
	where = environment(me);

       if ( ! me->query("special_skill/lonely") ) return 0;
 
	if (me->is_busy() || me->query_temp("pending/mingsi") 
           ||  me->query("doing") )
		return notify_fail("你现在正忙着呢。\n");

	if (where->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (me->is_fighting())
		return notify_fail("战斗中还是好好的凝神对敌吧。\n");

      if (where->is_chat_room())
              return notify_fail("你不能在聊天室里面冥思。\n");	

	if ((int)me->query("jing") * 100 / (int)me->query("max_jing") < 80)
		return notify_fail("你现在精力不支，无法冥思！\n");

	if ((int)me->query("qi") * 100 / (int)me->query("max_qi") < 80)
		return notify_fail("你现在体力不支，无法冥思！\n");

	me->set_temp("pending/mingsi", 1);    
       me->set_temp("mingsi/time",  10 + random(5) );
   
       me->set_short_desc("正在盘腿冥思。");

	message_vision("$N凝神闭目，盘腿打坐，开始冥思。\n", me);

	me->start_busy(bind((:call_other, __FILE__, "mingsi" :), me),
                       bind((:call_other, __FILE__, "halt_mingsi" :), me));
       return 1;
}

int mingsi(object me)
{
        
    if ( me->query_temp("mingsi/time") > 0 )
    {
       if ( me->query("potential") <= me->query_potential_limit() ) 
           me->add("potential", 7 + random(8));

       if ( me->query("experience") <= me->query_experience_limit() )
           me->add("experience", ( 7 + random(8) ) / 2 + random (2));

   
           me->add("combat_exp",  10 + random(5));
     
       me->add_temp("mingsi/time", -1);       
       return 1;
    }
       me->delete_temp("mingsi");
	me->delete_temp("pending/mingsi");
       me->set_short_desc(0);

    if ( me->query("potential") >= me->query_potential_limit() ) 

       write("你冥思完毕，感到自己的潜能似乎已经达到了上限。\n");
    else 
    if ( me->query("experience") >= me->query_experience_limit() )

       write("你冥思完毕，感到自己的实战体会似乎已经达到了上限。\n");
    else
       write("你冥思完毕，感觉神清气爽，似乎潜能和实战体会都有了进步。\n");

       message("vision", me->name() + "缓缓睁开双眼，结束了这次冥思。\n",
                        environment(me), ({ me }));	
}

int halt_mingsi(object me)
{
        tell_object(me, "你忽然回过神来，不再凝神冥思。\n");
        tell_room(environment(me), me->name() + "忽然睁开双眼，停止了冥思。\n", me);
	 me->delete_temp("pending/mingsi");
        me->delete_temp("mingsi");
        me->set_short_desc(0);
	 return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : mingsi

天煞孤星使用这个指令可以迅速地增加潜能和实战体会。

HELP );
        return 1;
}
