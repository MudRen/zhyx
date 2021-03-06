// jiutian.c 九天式

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp, ap1, dp1;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("「九天式」只能对战斗中的对手使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("天山六阳掌只有空手才能够使用！\n");

	if ((int)me->query_skill("liuyang-zhang", 1) < 120)
		return notify_fail("你的六阳掌法不够娴熟，不会使用「九天式」。\n");
	                        
        if ((int)me->query_skill("force") < 150)
		return notify_fail("你的内功修为不够高，难以运用「九天式」。\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("你现在真气不够，不能使用「九天式」。\n");
			
	msg = HIC "$N" HIC "双掌一振，化出满天掌影，团团笼罩住$n" HIC "！\n" NOR;

        ap = me->query_skill("force") + me->query_str()*10;
	ap += me->query("jiali")*2/3;
        dp = target->query_skill("force") + me->query_dex()*10;

        if (ap / 2 + random(ap) > dp || !living(target))
	{
		damage = me->query_skill("strike") + ap - dp;
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$p" HIR "无奈，只能硬挡一招，结果被$P"
                                           HIR "震得连退数步，吐血不止！\n" NOR);

		if (me->query_skill_mapped("force") == "bahuang-gong")
		{
			ap1 = me->query_skill("force");
			ap1 += me->query("jiali");
			ap1 += random(ap1/2);
			dp1 = target->query_skill("force");
			dp1 += target->query("jiali");
			dp1 += random(dp1/2);
			if (ap1 > dp1)
			{
		                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, ap1, 60,
		                           HIM "$p" HIM "尚未来得及调气养息，结果发现$P"
                                           HIM "六阳掌中混合入强劲的八荒六合唯我独尊功劲气！\n未及提防之下，强大的气息冲入身体，不由张口狂碰一口鲜血！\n" NOR);
			}
		}
		if (me->query_skill_mapped("force") == "beiming-shengong")
		{
			ap1 = me->query_skill("force");
			ap1 += me->query("jiali");
			ap1 += random(ap1/2);
			dp1 = target->query_skill("force");
			dp1 += target->query("jiali");
			dp1 += random(dp1/2);
			if (ap1 > dp1)
			{
                                target->add("neili",-ap1*2);
				if (target->query("neili") < 0)
					target->set("neili",0);
		                msg += HIM + target->name() + HIM + "尚未来得及调气养息，结果发现" + me->name() +
                                       HIM + "六阳掌中混合使用了北冥神功！\n未及提防之下，浑身内力飞泄而出，不由面如土色！\n" NOR;
			}
		}
                me->add("neili",-200);
		target->start_busy(1+random(2));
		me->start_busy(2+random(2));
	} else
	{
		msg += HIC "可是$p" HIC "强运内力，硬生生的挡住$P"
                       HIC "这一掌，没有受到任何伤害！\n"NOR;
		me->add("neili", -50);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
