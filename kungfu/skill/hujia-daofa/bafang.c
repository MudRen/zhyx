// bafang.c 八方藏刀式

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, dp;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「八方藏刀式」只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("手中没刀还使什么「八方藏刀式」！\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够！\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 100)
                return notify_fail("你的胡家刀法还不到家，无法使用「八方藏刀式」！\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你没有激发胡家刀法，无法使用「八方藏刀式」！\n");

        msg = HIW "$N" HIW "轻舒猿臂，手中的" + weapon->name() +
              HIW "吞吞吐吐，变化莫测，笼罩了$n" HIW "周身要害！\n" NOR;

        if (living(target))
                dp = target->query_skill("parry") / 2;
        else    dp = 0;

        if (random(me->query_skill("blade")) > dp)
        {
                msg += HIY "$n" HIY "见来招实在是变幻莫测，不由得心"
                       "生惧意，招式登时出了破绽！\n" NOR;
                count = me->query_skill("hujia-daofa", 1) / 6;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，打起精神小心接招。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        me->add("neili", -150);
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count/2);

        for (i = 0; i < 4 + random(4); i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count/2);
        me->start_busy(1 + random(6));
        return 1;
}

