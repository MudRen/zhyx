// juemi.c 天地绝灭
// updated by kasumi 2007/4/4
// 命中对手后，降低对手的jifa force，dodge，parry
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
string attack1(object me, object target, int damage);
 
int perform(object me, object target)
{
  object weapon;
	string msg;
	int ap, dp;
  int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("天地绝灭只能对战斗中的对手使用。\n");
 
	if (me->query_skill("never-defeated", 1) < 250)
		return notify_fail("你的不败神功还不够娴熟，不能使用天地绝灭！\n");

        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你必须手持兵刃才能施展天地绝灭！\n");

        if (me->query("neili") < 500)
                return notify_fail("你的内力不够，不能使用天地绝灭！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
              
       if (target->query_temp("never_juemie"))
                return notify_fail("对方现在已经无力防御，放胆攻击吧。\n");
              
              
  message_vision(HIC "$N" HIC "随便走了几步，忽然一荡手中的" + weapon->name() +
                 HIC "，迅捷无比的扫向$n" HIC "，变化复杂之极，不可思议！\n"
                       NOR, me, target);	
 
	ap = me->query_skill("never-defeated", 1);
	dp = target->query_skill("dodge",1); 
	
        if (ap * 2 / 3 + random(ap*2) > dp)
        {        	
           damage = ap*5 + random(ap*3);
           me->start_busy(3+random(3));
           me->add("neili", -400);
                
          msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   (: attack1, me, target, damage :));    
                        		
        } else
	      {
	       	msg = HIG "只见$n" HIG "并不慌张，只是轻轻一闪，就躲过了$N"
	               HIG "这一击！\n"NOR;
	         me->start_busy(2+random(3));
           me->add("neili", -400);
	      }

	message_vision(msg, me, target);
	return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "连忙格挡，可是这一招实在是鬼神莫"
                           "测，哪里琢磨得透？登时中了$P" HIR "的重创！\n" NOR;

        if (! target->query_temp("never_juemie"))
        {
                msg += HIM "$n只觉得恍如灵魂出窍，全身的力气竟似一丝"
                       "丝远离自己而去，无助之极。\n" NOR;

                target->add_temp("apply/force", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("never_juemie", 1);
        }
        call_out("juemie_end", 15 + random(15), me, target);
        return msg;
}

void juemie_end(object me, object target)
{
        if (target && target->query_temp("never_juemie"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口气，脸色由"
                                        "白转红，看起来好多了。\n" NOR, target);                       
                }                
                target->add_temp("apply/force", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                target->delete_temp("never_juemie");
        }
        return;
}