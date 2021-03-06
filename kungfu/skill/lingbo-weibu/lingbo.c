// This program is a part of NITAN MudLIB
// 能busy人，还能降对方的有效dodge，更能在凌波到1000级后无busy，是一大辅助技能。

#include <ansi.h>
#include <combat.h>

#define LING "「" HIW "洛神凌波" NOR "」"

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);


int perform(object me, object target)
{
        string msg;
        int level, ap, dp, count, counta;
        int tm;
        
        if (! target) target = offensive_target(me); 
        if (! target || ! target->is_character() || ! me->is_fighting(target)) 
                return notify_fail("你一个人跳甚么？\n");

        if (userp(me) && ! me->query("can_perform/lingbo-weibu/ling"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if ( me->query_temp("no_lingbo") ) 
                return notify_fail("你刚刚使用过洛神凌波，步伐还未平复！\n" NOR);             

        if ((level = me->query_skill("lingbo-weibu", 1)) < 120)
                return notify_fail("你的凌波微步还不够熟练，难以施展" LING "。\n" NOR);

        if ((int)me->query("neili") < 600)
                return notify_fail("你现在真气不足，难以施展" LING "。\n" NOR);


        if( me->query("gender") == "女性")
               msg = HIW "\n$N" HIW "提起真气，依照先天伏羲六十"
                     "四卦，将凌波微步由头到尾迅速无比的走了一次。\n"
                     HIW"$N" HIW "仿如洛神再生，身形顿时轻盈无比，"
                     "微步凌波，真个将逍遥二字发挥得淋漓尽至。\n" NOR;

        else   msg = HIC "\n$N" HIC "提起真气，依照先天伏羲六十"
                     "四卦，将凌波微步由头到尾迅速无比的走了一次。\n"
                     HIC"只见$N" HIC "意态飘逸，影子乱飞，身形顿时轻"
                     "盈无比，真个将逍遥二字发挥得淋漓尽至。\n" NOR;

        message_combatd(msg, me, target);
        count = level / 2;
        counta = 4 - (int)level / 249;
        if (counta < 0) counta = 0;
        	  
	      ap = me->query_skill("dodge");
	      dp = target->query_skill("dodge",1);   // 大辅助，所以命中略高

                   
        if (ap / 2 + random(ap) > dp)
        {      
	              me->set_temp("no_lingbo",1);
                call_out("lingbo_ok", 3+random(3), me);       
                msg = HIW "$N犹如神仙下凡，$n跟随着$N的舞步转了个头晕眼花。\n" NOR;          
                if (! target->is_busy())
                  target->start_busy(3 + random(level / 100));
                if (! target->query_temp("lb_ling") && !userp(target))
                	{
                		msg += HIW "$n手脚竟然也不听使唤了！\n" NOR;  
                		target->add_temp("apply/dodge", -count);    // 对一个人只能成功用一次
                		target->set_temp("lb_ling", 1);                	      
                	}
                	
                me->add("neili", -400);
                me->start_busy(counta);    // 凌波微步到1000级以后，此招将没有busy
        } else 
        {
                msg = HIG "可是$n看破了$N的舞步,仪态从容的躲了过去\n" NOR;
                me->add("neili", -100);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;

}

void lingbo_ok(object me) {
  if (!me) return;
  me->delete_temp("no_lingbo");
}


