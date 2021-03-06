#include <ansi.h>
#include <combat.h>

#define YH "「" HIR "移魂大法" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        string msg,dodge_str,parry_str;
        int ap, dp, damage;
        int i,skill,times;
		object weapon;	

        me = this_player();  

		skill = (int) me->query_skill("jiuyin-shengong",1);
		times = 4 + skill / 80;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YH "只能在战斗中对对手使用。\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 400)
                return notify_fail("你九阴神功不够娴熟，难以施展" YH "。\n");
 
        if ((int)me->query_skill("force", 1) < 350)
                return notify_fail("你内功根基不够，难以施展" YH "。\n");   

        if (me->query_skill_mapped("force") != "jiuyin-shengong")
                return notify_fail("你没有激发九阴神功为内功，难以施展" YH "。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在的真气不够，难以施展" YH "。\n");

		
	    if(me->query_temp("no_yihun"))
                return notify_fail("你内息未稳，无法使用" YH "！\n");     

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
                            
        msg = HIM "\n$N" HIM "猛然间尖啸一声，施展出九阴神功中的「" HIR "移魂大法" HIM"」。"
              "只见$N" HIM "各种招式千奇百怪、变化多端，脸上喜怒哀乐，怪状百出。\n" NOR;

		dodge_str=target->query_skill_mapped("dodge");
		parry_str=target->query_skill_mapped("parry");
        ap = me->query_skill("jiuyin-shengong", 1) + me->query_skill("force", 1);
        dp = target->query_skill("jiuyin-shengong", 1) + target->query_skill("force", 1);

        if (ap * 11 / 20 + random(ap) > dp)
        {
             msg += HIG "$n" HIG "看了准备取笑$N，却不知不觉的学起$N的表情。" HIG
                    "$N猛然做出向自己攻击的动作，$n立刻向自己发疯似的攻击起来，出手越来越重！\n" NOR; 
			 message_sort(msg, me, target);			
		 
			 target->map_skill("dodge", 0);
			 target->map_skill("parry", 0);
            
		     for (i = 0; i < times; i++)
		     {
				       if (! me->is_fighting(target))
                        break;
                      
					   if (objectp(weapon = target->query_temp("weapon")))
			               COMBAT_D->do_attack(target, target, weapon, 0);
					   else COMBAT_D->do_attack(target, target, 0, 0);
		      }
	
		    target->map_skill("dodge", dodge_str);
			 target->map_skill("parry", parry_str);
		 
            
			me->start_busy(2 + random(4));
             me->add("neili", -600);
            

        } else
        {
              msg += NOR + CYN "$n" NOR + CYN "怒喝道：“尔等妖法，休想迷惑我！”。猛然间，招式陡快，"
                     "竟将$N" NOR + CYN "这招破去。\n" NOR;
			  message_sort(msg, me, target);

              me->add("neili", -200);
              me->start_busy(1 + random(2));
        }

		me->set_temp("no_yihun",1);
		call_out("yihun_ok", 3 + random(2), me);    

        return 1;
}

void yihun_ok(object me)
{
	if (!me) return;
	me->delete_temp("no_yihun");
}