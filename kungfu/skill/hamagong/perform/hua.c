// hua.c 一气化九百 by kasumi 2015.2.24

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define HUA "「" HIW "一气化九百" NOR "」"

int perform(object me, object target)
{
        string msg,str;
        int n,damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! me->query("reborn")){
                return notify_fail("你没有经历过转世重生，无法领悟蛤蟆功绝学「一气化九百」。\n");
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「一气化九百」只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUA "只能空手使用。\n");
                
        if ((int)me->query("neili") < 1000)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("hamagong", 1) < 500)
                return notify_fail("你的蛤蟆功火候不够，无法施展" HUA "。\n");

        if ((int)me->query_skill("force") < 600)
                return notify_fail("你的内功修为不够，无法施展" HUA "。\n");

        if (me->query_skill_prepared("unarmed") != "hamagong")
                return notify_fail("你现在没有准备使用蛤蟆功，无法施展" HUA "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
			  

        msg = HIY"$N"HIY"“阁阁”的大叫数声，运起蛤蟆功劲力，双腿一弯双掌齐发，向前推出......\n"
              HIG"这一推实乃$N"HIG"毕生功力之所聚，$n猛然感受到山洪海啸般的劲力袭来。\n" NOR;   
        damage = me->query_skill("force",1)/3+me->query_skill("hamagong",1)/2;
        damage = damage + random (damage/2);

		msg += HIM"                      突！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIG"                      突！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIY"                      突！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIR"                      突！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIC"                      破！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIW"                      破！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIY"                      破！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIG"                      破！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
		                           HIR "$n" HIR "登时觉得气血不畅，“哇”的吐出了一口鲜血！\n" NOR);
		msg += HIW"                  一气化九百！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
		                           HIR "$n" HIR "被震得如同断线的风筝般飞了出去！\n" NOR);
		
		
		message_combatd(msg, me, target);
        me->add("neili", -900);
        me->start_busy(3+random(4));
        return 1;
}
