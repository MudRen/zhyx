// zhangzhen.c 掌震中华

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHANGZHEN "「" HIW "掌震中华" NOR "」"

int perform(object me, object target)
{
	string msg;
        int ap, dp;
        int i, times, count, damage;

        if (userp(me) && ! me->query("can_perform/china-aojue/zhangzhen"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(ZHANGZHEN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("此招只能空手施展！\n");

	if ((int)me->query_skill("china-aojue", 1) < 200)
		return notify_fail("你的中华傲诀不够深厚，不会使用" ZHANGZHEN "。\n");	

        if ( me->query_skill_prepared("strike") != "china-aojue")
                return notify_fail("你没有准备使用中华傲诀，无法施展" ZHANGZHEN "。\n");

	if ( me->query("neili") < 500 )
		return notify_fail("你的内力不够，不能使用" ZHANGZHEN "。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("china-aojue", 1);
        dp = target->query_skill("parry", 1);


        msg = HIW "$N" HIW "怒喝一声，双手大开大合，"
              "毫无花巧地向$n各攻击出一掌！\n" NOR;

        if (ap * 4 / 5 + random(ap) > dp)
        { 
                damage = ap * 3 / 2 + random(ap);
                me->add("neili", -300);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "只见$n" HIR "一个招架不稳，胸口已被"
                                           "$N双掌拍中，顿时呕出几口鲜血！\n" NOR);
        } else
        {
                me->add("neili", -100);                
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                       "招架，急忙提气跃开。\n" NOR;
        }

         message_sort(msg, me, target);


	
         msg = HIY "紧接着$N" HIY "双掌交击，连出九掌，势如排山倒海般向$n"
              HIY "逼去！\n" NOR;
        
        count = ap / 9;

        if (count > 60 ) count = 60;

        me->add_temp("apply/attack", count);
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, i * 3 );
        }
        me->start_busy(2 + random(3));
        me->add("neili", -200);

        me->add_temp("apply/attack", -count);
	 message_combatd(msg, me, target);

	return 1;
}
