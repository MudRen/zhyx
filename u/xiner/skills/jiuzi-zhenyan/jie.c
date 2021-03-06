// jie.c 天劫由手印PFM的升级版
// update by xiner 20090218

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「天劫」只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("「天劫」只能空手使用。\n");
                
        if (me->query("max_neili") < 5000)
                return notify_fail("你的内力修为还不够，无法施展天劫。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query("qi") < 1000)
                return notify_fail("你的体力现在不够！\n");

        if ((int)me->query_skill("jiuzi-zhenyan", 1) < 250)
                return notify_fail("你的九字真言火候不够，无法使用天劫！\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("你的内功修为不够，无法使用天劫！\n");

        if (me->query_skill_prepared("hand") != "jiuzi-zhenyan")
              return notify_fail("你现在没有准备使用九字真言，无法使用天劫！\n");

        msg = HIW "$N" HIW "一声暴喝，双手猛然翻滚，"
              "刹那间只见无数的手印铺天盖地蜂拥而出，"
              "气势恢弘，无与伦比。\n" NOR;

        ap = me->query_skill("hand") + me->query_skill("buddhism") + me->query_skill("lamaism");

        dp = target->query_skill("parry") + target->query_skill("buddhism") + target->query_skill("lamaism");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                count = ap / 8;
                msg += HIR "$n" HIR "面对$P" HIR "这排山倒海攻势，完全"
                       "无法抵挡，唯有退后。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神应战，竭尽所能化解$P" HIC
                       "这几掌。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -500);
        me->add("qi", -200);    
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));
        me->add_temp("apply/attack", -count);

        return 1;
}