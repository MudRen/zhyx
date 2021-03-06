// powerup.c 修罗阴煞功驱蛇 by Kasumi

#include <ansi.h>
inherit F_SSERVER;
inherit F_CLEAN_UP;

void snake_hit(object me, object target);

int exert(object me, object target)
{
	int times;
	object weapon;

	if (target != me)
		return notify_fail("你只能放蛇在自己的兵器上。\n");

	if ( !objectp(weapon = me->query_temp("weapon")))
               return notify_fail("你必须装备兵器才能让蛇缠在上面。\n");

	if (me->query("family/family_name") != "五毒教")     
                return notify_fail("只有五毒教弟子才能驱蛇。\n");    

	 if( me->query_skill("xiuluo-yinshagong",1) < 350 )
                return notify_fail("你的修罗阴煞功太差，无法驱蛇！\n");

	if ((int)me->query("neili") < 500 )
		return notify_fail("你的内力不够无法驱蛇。\n");

	if ((int)me->query_temp("snake"))
		return notify_fail("你已经驱了蛇在兵器上了。\n");

	times =  me->query_skill("xiuluo-yinshagong",1)/40;
	if (times > 20)
       times = 20;
	   
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIM "$N" HIM "拿出一根竹管轻轻地吹了起来，只听“嗖”的一声，一条怪蛇窜到了" + weapon->name()+ HIM"缠了起来！\n" NOR, me);
	me->set_temp("snake", times);
    call_out("snake_hit",1, me,target);
	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void snake_hit(object me, object target)
{
    object weapon;
	object *victim;
	string msg,name;
	string *parts=({ "头部", "左手", "右手", "左腿", "右腿", "胸口", "背部"});
	string part;
	int damage,i;

	if (!objectp(me) || !objectp(weapon = me->query_temp("weapon")))
       return;
               
	if (me->query_temp("snake") > 1)
	{
		me->set_temp("snake", me->query_temp("snake") -1);
 		if (me->is_fighting())
		{
			part = parts[random(sizeof(parts))];
			switch (part)
			{
			case "头部":
			    damage = target->query("max_qi") * 0.3;
				break;
			case "左手":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "右手":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "左腿":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "右腿":
			    damage = target->query("max_qi") * 0.1;
				break;
			case "胸口":
			    damage = target->query("max_qi") * 0.2;
				break;
			case "背部":
			    damage = target->query("max_qi") * 0.2;
				break;
			}
			victim = me->query_enemy();
			for (i = 0; i < sizeof(victim); i++)
			{
				victim[i]->receive_wound("qi", damage, me);
				name = victim[i]->name();
				msg = HIM"只见怪蛇吞吐伸缩，猛然张口在"+ name+ HIM"的"HIR"“" + part + HIR"”"HIM"狠狠地咬了一口！\n"NOR;				
				message("vision", msg, environment(me), ({ victim[i] }));
			}
				
		}
		else
		{
		    msg = HIG "$N" HIG "手中" + weapon->name()+ HIG"上面缠绕着一条怪蛇，“丝丝”地吐着"HIR"红信"HIG"！\n" NOR;
			message_combatd(msg, me);
		}
	 	remove_call_out("snake_hit");
		call_out("snake_hit",3, me,target);
		return ;
	}
 	else 
	{
	    me->delete_temp("snake");
		msg = HIY "盘绕在$N" + weapon->name()+ HIY"上的怪蛇，“嗖”的一声窜到地上不见了踪影！\n" NOR;
		message_combatd(msg, me);
		return ;
	} 
} 
