#include <ansi.h>
#include <combat.h>


#define YIN "「" HIR "九阴九阳" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,name;
        int ap, dp;
        int damage;
	object equipment;

//        if (userp(me) && ! me->query("can_perform/yinyang-shiertian/yinyang"))
//                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YIN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(YIN "只能空手施展。\n");

        if ((int)me->query_skill("yinyang-shiertian", 1) < 300)
                return notify_fail("你阴阳九转十二重天火候不够，难以施展" YIN "。\n");

        if (me->query_skill_mapped("force") != "yinyang-shiertian")
                return notify_fail("你没有激发阴阳九转十二重天为内功，难以施展" YIN "。\n");

        if (me->query_skill_mapped("unarmed") != "yinyang-shiertian")
                return notify_fail("你没有激发阴阳九转十二重天，难以施展" YIN "。\n");

        if (me->query_skill_prepared("unarmed") != "yinyang-shiertian")
                return notify_fail("你没有准备阴阳九转十二重天，难以施展" YIN "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，难以施展" YIN "。\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("你的内力修为不够，难以施展" YIN "。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在的真气不足，难以施展" YIN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "施出阴阳九转十二重天绝技「" HIR "九阴九阳"
		HIY "」，右手成爪，忽的抓向$n的要穴！\n\n" NOR;     

//        ap = me->query_skill("strike") + me->query("str") * 10;
//        dp = target->query_skill("parry") + target->query("con") * 10;
//        dd = target->query_skill("dodge") + target->query("dex") * 10;

        ap = me->query_skill("yinyang-shiertian", 1) * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

	if (ap * 3 / 4 + random(ap) > dp)
        {
		damage = ap * 5 + random(ap * 2);
		me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
				HIR "只听“扑哧”一声，$N" HIR "五指正插入$n" HIR "的要害，$n"
				HIR "一声惨叫，血射五步。\n"  NOR);
	}
	else
        {
		me->add("neili", -200);
		msg += HIC "$n" HIC "暗叫不好，急忙闪头，可是$N"
			HIC "手臂咔咔作响，忽然暴长，迅论无比的抓向$n。\n" NOR;

		if (ap * 3 / 4 + random(ap) > dp)
                {
			damage = ap * 5 + random(ap * 2);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
					HIR "$n" HIR "哪里料到$N" HIR
					"竟有如此变招，不及躲闪，肩头被$P"
					HIR "抓了个鲜血淋漓。\n" NOR);
                } else
                        msg += CYN "$n" CYN "不及多想，急切间飘然而退，让$N"
                               CYN "这一招无功而返。\n" NOR;
        }

        msg += HIY "\n紧接着$N" HIY "双目微闭，左手手掌单手托天。掌心顿时腾起一个无比刺眼的气团。\n"
		"随即$N" HIY "收拢掌心，气团爆裂开来，向四周电射而出，光芒足以和日月争辉。\n" NOR;


        ap = me->query_skill("yinyang-shiertian", 1) * 3 / 2 + me->query_str() * 5;
        dp = target->query_skill("parry") + target->query_dex() * 5;

	if (ap * 3 / 4 + random(ap) > dp)
        {
		me->add("neili", -300);
                damage = ap * 5 + random(ap);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
				HIR "\n$n"HIR"急忙抽身后退，可只见眼前光芒暴涨，一闪而过。"
				"全身已多了数个伤口，鲜血飞溅。\n" NOR);
		target->start_busy(2 + random(3));
        } else
        {
		me->add("neili", -200);
		msg += HIC "\n$n" HIC "只觉眼前金光万道，周围空气几欲沸腾，大惊之下连忙急运内功抵御。\n" NOR;

		if (ap * 3 / 4 + random(ap) > dp)
                {
			me->add("neili", -200);
                	damage = ap * 5 + random(ap);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
					HIR "然而光芒便如千万细针一般扎入$n"HIR"身体内。\n光芒闪过，"
					"$n"HIR"七窍流血，神情扭曲，煞是恐怖。\n" NOR);
			target->start_busy(2 + random(3));
                } else
		{
			me->add("neili", -100);
                        msg += CYN "只见光芒收敛，$n堪堪抵御住这招，" NOR;
			target->start_busy(3 + random(3));
			//破防具
			if (objectp(equipment = target->query_temp("armor/cloth")))
			{
				if (equipment->query("consistence") < 30)
				{
					name = equipment->name();
					equipment->set("consistence", 0);
					equipment->move(environment(me));
					msg +=CYN "然而$n身着的" + name + HIC "已经被烧焦了。\n" NOR;
				}
				else
				{
					name = equipment->name();                                      
					equipment->add("consistence", -20);
					msg +=CYN "然而$n" CYN "身上的" + name + CYN "却已经破损不堪。\n" NOR;
				}
			}
			else
				msg +=CYN "然而$n" CYN "身上的衣服竟已经没有了！\n" NOR;				
		}
        }
	message_combatd(msg, me, target);
        me->start_busy(1 + random(2));
        me->add("neili", -500);
        return 1;
}
