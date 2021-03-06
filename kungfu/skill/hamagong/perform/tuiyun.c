// tui.c 推天式之运

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void yun_remove(object me,object target); 
int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「推天式」之运式只能对战斗中的对手使用。\n");

        if ( objectp(me->query_temp("weapon")) )
	         return notify_fail("你手持兵器，无法施展蛤蟆功的绝技。\n");
	         
	      if ((int)me->query_temp("tuitimes"))
                return notify_fail("你已经运起蛤蟆功的「推天式」了。\n");

        skill = me->query_skill("hamagong", 1);

        if (skill < 280)
                return notify_fail("你的蛤蟆功修为不够精深，不能使用「推天式」！\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("你的内力修为不够深厚，无法施展「推天式」！\n");

        if (me->query("neili") < 600)
                return notify_fail("你的真气不够，无法运用「推天式」！\n");

        msg = HIY "$N" HIY "“呼”的一下翻身趴在地上，“嗝”的一声大叫，两个腮帮子一鼓，蓄势待发......\n" NOR;   
        me->set_temp("tuitimes", 1);
		me->set("qi",me->query("qi")*2);
		me->add_temp("apply/armor", skill*5);
        message_combatd(msg, me, target);
        me->start_busy(1+random(2));
		call_out("yun_remove", 60, me);    
        return 1;
}

void yun_remove(object me,object target) 
{
  string msg;
  int skill;
  skill = me->query_skill("hamagong", 1);
  if (!me) return;
  if ((int)me->query_temp("tuitimes"))
  {  
     msg = HIY "$N" HIY "的蛤蟆神功推天式运了半天都没有发，就泄了。\n" NOR;  
     message_combatd(msg, me, target);	
     me->add_temp("apply/armor", -skill);	 
     me->delete_temp("tuitimes");
  }
  return;
}
