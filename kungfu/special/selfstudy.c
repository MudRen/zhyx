//selfstudy.c 无师自通
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "无师自通" NOR; }

int perform(object me, string skill)
{        	
	int lvl1, lvl2, lvl3, lvl4, lvl5, lvl6;

	if (! me->query("reborn"))        
            return notify_fail("你尚未转世重生，无法使用此技能！\n");
      
	lvl1 = me->query_skill("literate", 1);
	lvl2 = me->query_skill("sanscrit", 1);
	lvl3 = me->query_skill("muslim", 1);
	lvl4 = me->query_skill("mathematics", 1);
	lvl5 = me->query_skill("qimen-wuxing", 1);
	lvl6 = me->query_skill("count", 1);

	if (lvl1 >= 600 && lvl2 >= 600 && lvl3 >= 600
	 && lvl4 >=400 && lvl5 >= 400 && lvl6 >= 400)
		return notify_fail("你现在无需使用此技能！\n");

	message_vision(HIC "$N" HIC "闭目端坐，冥神思索，试图"
                       "回忆前世所学。\n" NOR, me);   

	me->set_short_desc("正端坐在地上冥思苦想");
	me->delete_temp("pending/selfstudy");   

	me->start_busy((:call_other, __FILE__, "check" :), 
                      (:call_other, __FILE__, "halt" :)); 
	return 1;
}

int check(object me)
{
    if ( me->add_temp("pending/selfstudy", 1) < (40 + random(10)) )
        return 1;
   
     message_vision(HIW "$N" HIW "缓缓睁开双目，"
                    "结束了这次冥想。\n" NOR, me);

     if (random(5) != 0 )
        tell_object(me, "\n你感到这次冥想并无多大进展，"
                        "无法回忆起前世所学的知识。\n\n");
     else
     {
        tell_object(me, HIG"\n突然你感到心智顿开，"
                         "无数世前所学的知识刹那间印入脑海。\n\n"NOR);
        tell_object(me, HIW"\n你自学成功了。\n\n"NOR);

	me->set_skill("literate", 600);
	me->set_skill("sanscrit", 600);
	me->set_skill("muslim", 600);
	me->set_skill("qimen-wuxing", 400);
	me->set_skill("mathematics", 400);
	me->set_skill("count", 400);
     }
    me->set_short_desc(0);  
    me->delete_temp("pending/selfstudy");
    return 0;
}

int halt(object me)
{            
	 message_vision(HIG"$N睁开双眼，结束了这此冥想。\n"NOR, me);        
        me->set_short_desc(0);  
        me->delete_temp("pending/selfstudy");     
        return 1;
}


