// Created by kasumi 
#include <ansi.h>
#include <combat.h>
#define WAN "「" HIY "万流奔腾" NOR "」"
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage,attack_time,i,lvl1,lvl2;
        int ap, dp, as,ds;
        string wp, msg,msg1,parry_str;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(WAN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" WAN "。\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("你的内功火候不够，难以施展" WAN "。\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 300)
                return notify_fail("你的玄铁剑法不够娴熟，难以施展" WAN "。\n");

        if ((int)weapon->query_weight() < 20000)
                return notify_fail("你手中的" + wp + "分量不够，难以施展" WAN "。\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("你现在的内力不足，难以施展" WAN "。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你没有激发玄铁剑法，难以施展" WAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	as=me->query("max_neili");
	ds=target->query("max_neili");
	parry_str=target->query_skill_mapped("parry");

			
	if (as/3 + random(as) > ds && random(2) == 1)
	{                                                                                                 
		call_out("kill_him", random(4)+1, me, target);                                             
		me->add("neili", -500);                                                                   
		msg = YEL "$N" YEL "忽然收起了所有的攻势，闭目向后撤回，似乎连杀气都一起消失了！\n" NOR;  
		msg += RED "然而无数气流却从$N身后飞出，$N脸色也越来越红！\n"NOR;                          
		message_combatd(msg, me ,target);                                                        
		return 1;                                                                                  
        }
     else
	{
		ap = me->query_skill("sword")+ me->query_str()*5;                                          
		dp = target->query_skill("parry") + target->query_dex()*4;   
		
		msg = HIC "$N" HIC"仰天长啸，手中" + wp + HIC"劈头盖脑的奔$n"HIC"砍去，霎时已劈出了无数剑。";                                                                    
		msg += HIC "四下"HIW"空气激荡回旋"HIC"，犹如"HIG"海浪涛涛叠叠"HIC"，将$n"HIC"团团卷在其中！\n" NOR;
		message_sort(msg, me, target);
		lvl1 = (int) me->query_skill("surge-force",1)/100;
		lvl2 = (int) me->query_skill("yunv-xinjing",1)/100;
		if (lvl1>lvl2)
		 lvl2=lvl1;
		attack_time = 3 + random(lvl2);
           if (attack_time > 6)
              attack_time = 6;		   
		for (i = 0; i < attack_time; i++)
		{
		   
		   target->map_skill("parry", 0);
		   target->add_temp("apply/parry", target->query_skill("parry",1));
		   
		   
		   msg1=HIR"                       $N大喝道：第"+chinese_number(i+1)+HIR"剑！\n\n"NOR;
		  
		   damage = me->query_skill("sword");
		   damage = damage + random(damage/2);
		   msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
		                           HIR "$n" HIR "大吃一惊，只觉得$N"HIR"内力有如潮水般涌至，眼前剑网闪亮，黑白难辨。\n"  NOR);	
		   message_combatd(msg1, me, target);
		   target->add_temp("apply/parry", - target->query_skill("parry",1));
		   target->map_skill("parry", parry_str);
		}
		
		me->start_busy(3 + random(5));
		return 1;
	}		
}       

void kill_him(object me, object target)                                                                    
{
        string msg;
        if(me->is_fighting() && target->is_fighting() &&
        environment(me) == environment(target))                                                            
        {                                                                                                  
         msg = HIR "气流在$n身后合拢，顿时$n被笼罩在一片潮水般的剑气中。\n"                                
         "剑气全部汇聚如洪水般冲向$n，当$n回头时一切都已经太晚，瞬间被淹没了。\n" ;                        
         msg +=  HIR"气浪过后，$N脸色已恢复平静，$n也倒在了地上。。。\n" NOR;                              
                                                                                                           
        message_combatd(msg, me, target);                                                                  
        target->unconcious();                                                                      
        }                                                                                                  
        me->start_busy(3);                                                                                 
        return;                                                                                           
}