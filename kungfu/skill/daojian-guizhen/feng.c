//created by kasumi
#include <ansi.h>
#include <combat.h>

#define FENG "「" HIW "千里冰封" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon, weapon2;
        int i, count, damage;
        int ap, dp;       

		if (me->query_skill("daojian-guizhen", 1) < 350)
                return notify_fail("你的刀剑归真等级不够，难以施展" FENG "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(FENG "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword"
           && (string)weapon->query("skill_type") != "blade" )
                return notify_fail("你所使用的武器不对，难以施展" FENG "。\n");

        type = weapon->query("skill_type");

        if (me->query_skill(type, 1) < 300)
                return notify_fail("你的" + to_chinese(type) + "太差，"
                                   "难以施展" FENG "。\n");

        if (me->query_skill_mapped(type) != "daojian-guizhen")
                return notify_fail("你没有激发刀剑归真，难以施展" FENG "。\n");        

        if (me->query("neili") < 600)
                return notify_fail("你现在的真气不够，难以施展" FENG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        

		msg = HIM "$N" HIM "脸色凝重，手中" + weapon->name() + HIM "寒气逼人，刃身撕裂空气，周围忽起阵阵杀机，温度骤降，\n"
			      "片片"HIW"雪花" HIM "飘落，$n" HIM "如堕冰窖，眉毛都蒙上了薄薄"HIW"白霜"HIM"！\n"
				  HIM "$N" HIM "一声怒吼：“千里冰封......”，\n"
				  HIM"只见"+ weapon->name()+ HIM "挟着漫天风雪，以雷霆之势扑向" HIM"$n，" HIM "天地为之变色！\n" + NOR;


        ap = me->query_skill("sword", 1) + me->query_skill("blade", 1);
        dp = target->query_skill("sword",1) + target->query_skill("blade",1);
		
		damage= ap * 3 + random(ap*2);

		if (ap * 2 / 3 + random(ap) > dp)
        {
			me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "$n" HIR "已然冻僵，哪能闪避，$N"
										   HIR "的寒气刃茫顿时透体而入，口中鲜血狂喷，连退数步。\n" NOR);
        } else
        {
			me->add("neili", -150);
                msg += CYN "$n" CYN "见势不妙，顾不上脸面，连着100个懒驴打滚，狼狈之至，险险避过$P的这记杀招。\n" NOR;
        }
		 message_combatd(msg, me, target);

	    msg = HIW "$N" HIW "余势未尽，招式陡然变得凌厉无比，一转念间已然攻出数招......\n" NOR;

        if (ap / 2 + random(ap * 2) > dp)
        {
                count = ap / 3;
                msg += HIR "$n" HIR "见$P" HIR "来势迅猛之极，一时不知该如"
                       "何作出抵挡，竟呆立当场。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "见$p" HIY "来势迅猛之极，甚难防备，连"
                       "忙振作精神，小心抵挡。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);
	
        me->add("neili", -300);
        me->add_temp("apply/attack", count);        
		me->set_temp("daojian-guizhen/max_pfm", 1);

		for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
				if (random(2)==1 && ! target->is_busy())
					target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

		me->add_temp("apply/attack", -count);
        me->delete_temp("daojian-guizhen/max_pfm");
        me->start_busy(2 + random(5));
       
        return 1;
}
