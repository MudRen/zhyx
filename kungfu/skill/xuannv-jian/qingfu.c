// qingfu.c 微风轻拂面
 
#include <ansi.h>
#include <combat.h>

#define QINGFU "「" HIG "微风轻拂面" NOR "」"
 
inherit F_SSERVER;
 
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
       weapon = me->query_temp("weapon");

        if ( ! me->query("can_perform/xuannv-jian/qingfu"))
                 return notify_fail("你所使用的外功中没有这种功能。\n");   

	if (! target || ! me->is_fighting(target))
		return notify_fail(QINGFU "只能对战斗中的对手使用。\n");
 
	if (me->query_skill("xuannv-jian", 1) < 180)
		return notify_fail("你的玄女剑法还不够娴熟，不能使用" QINGFU "。\n"); 

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你手里拿的不是剑，怎么施展" QINGFU "？\n");                 

        if (weapon && me->query_skill_mapped("sword") != "xuannv-jian")
                return notify_fail("你没有准备使用玄女剑法，难以施展" QINGFU "。\n");

        if (me->query("neili") < 300)
                return notify_fail("你的内力不够，不能使用" QINGFU "！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIG"$N摆动手中利剑，似乎毫不使力，犹如一阵微风轻轻拂向$n面风。\n" NOR;
 
	ap = me->query_skill("xuannv-jian", 1) * 2 + me->query("per") * 20 + me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry",1) + target->query("per") * 20 + target->query_skill("martial-cognize", 1);

        me->start_busy(1);
        me->add("neili", -100);

        if (ap * 4/5 + random(ap) > dp)
        {
        	 me->add("neili",-50);
           damage = ap * 2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70+random(30),
                                           HIR "$n" HIR "以为此招平淡无奇，疏于防范，结果被$N"
                                           HIR "一剑刺中面门，鲜血溅了一地！\n" NOR);
		
        } else
	      {
		       msg += HIC "然而$n" HIC "不为此招幻象所惑，小心应付，将$N" HIC
                       "此招一一化解。\n" NOR;
	      }

	message_combatd(msg, me, target);
	return 1;
}
