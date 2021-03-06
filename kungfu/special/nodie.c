// nodie.c 不死金身

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "不死金身" NOR; }

int perform(object me)
{
      
       if (! me->query("reborn"))        
            return notify_fail("你尚未转世重生，无法使用此技能！\n");

       if ( time() - me->query("la_sp_tm/nodie") < 600 )        
            return notify_fail("你要过些时候才能再用此技能！\n");

        message_vision(YEL "$N" YEL "脸色一沉，全身散发出一阵金光，"
                       "便如罗汉转世一般。\n" NOR, me);
       
       me->set_temp("no_die",1);
       me->set("la_sp_tm/nodie", time());        

   	me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 60);

        return 1;
}

void remove_effect(object me)
{
     me->delete_temp("no_die");
     tell_object(me, "你施展完不死金身，松了一口气。\n");
}
