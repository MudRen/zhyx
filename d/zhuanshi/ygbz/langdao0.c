// yuchang
#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "廊道");
        set("long", @LONG 
这是又一个廊道,末端没入暗黑里，令人难测远近 
深浅，但扑面而来的空气更觉清新!

LONG
        ); 
        set("exits", ([ 
            "north"  : __DIR__"langdao0",
            "south"  : __DIR__"langdao0",
            "west"  : __DIR__"langdao3",
            "east"  : __DIR__"langdao2",
        ]));      
       setup();
}
void init()
{
    object me;
    string msg;
    me = this_player();  

   if ( me->query_skill("dodge",1) >= 620 
        && me->query("neili") > 1000) 
   {
       msg =  HIB"\n$N跨步入门，忽然机括疾响。"
             "十枝特长特粗的精钢箭矢，似是杂乱无章的从另一端暗 "
             "黑处疾射而至，破空声带起激厉的呼啸声，在这寂静的地下"
             "廊道更份外刺耳。$N身形一移，躲过了箭矢!" 
             "但是还是用了不少内力!\n\n"NOR;

      message_sort(msg, me);
      me->add("neili", - me->query("max_qi") / 5); 
      if ( me->query("neili") < 0 )
           me->set("neili", 0);
   
  } else
  if ( me->query_skill("dodge",1) >= 600 ) 
  {     
     msg = HIR"$N跨步入门，忽然机括疾响。"
           "十枝特长特粗的精钢箭矢，似是杂乱无章的从另一端暗"
           "黑处疾射而至，破空声带起激厉的呼啸声，在这寂静的地下"
           "廊道更份外刺耳。$N想躲过箭矢，但是由于轻功不到家，被箭矢" 
           "射中了，造成了重伤!\n"NOR;

     message_sort(msg, me);
     me->set_temp("die_reason", "被乱箭射死了");
     me->receive_wound("qi", me->query("max_qi") / 5);
  }    
  else
  {
    msg = HIR"$N跨步入门，忽然机括疾响。"
          "十枝特长特粗的精钢箭矢，似是杂乱无章的从另一端暗"
          "黑处疾射而至，破空声带起激厉的呼啸声，在这寂静的地下"
          "廊道更份外刺耳。$N想躲过箭矢，但是轻功不够，顿时被" 
          "射成了一只刺猬！\n"NOR;
     message_sort(msg, me);

    me->set_temp("die_reason", "被乱箭射死了");
    me->die();  
  }
}