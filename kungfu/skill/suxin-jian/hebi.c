#include <ansi.h>
#include <combat.h>

#define HEBI "「" HIG "双剑"HIY"合璧" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type1, type2, msg;
        object weapon1, weapon2;
        int ap, dp, damage,i,n,count;
        
        if (userp(me) && ! me->query("can_perform/suxin-jian/hebi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (me->query_skill("suxin-jian", 1) < 200)
                return notify_fail("你的玉女素心剑法等级不够无法使用" HEBI " 。\n");
        
        if (me->query_skill("quanzhen-jian", 1) < 200)
                return notify_fail("你的全真剑法等级不够无法使用" HEBI " 。\n");
                
        if (me->query_skill("zuoyou-hubo", 1) < 100)
                return notify_fail("你的左右互搏技能等级不够无法使用" HEBI " 。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(HEBI "只能对战斗中的对手使用。\n");

        weapon1 = me->query_temp("weapon");
        weapon2 = me->query_temp("handing");

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("你没有同时装备双剑，难以施展" HEBI "。\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("你的" + weapon2->name() + "已经严重"
                                   "损坏，无法继续使用了。\n");       

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail(HEBI"需要激发玉女素心剑发起。\n");        

        if (me->query("neili") < 500)
                return notify_fail("你现在的真气不够，难以施展" HEBI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
                
        msg = HIW "$N" HIW "心如止水，双剑一错，双手分使全真剑法和玉女剑法，翩然攻出数招。\n" NOR;
        msg +=HIR "$n" HIR "看到$N" HIR "双剑飞舞，招式中所有破绽都为另一剑补去，不知如何招架！\n"NOR;
        message_combatd(msg, me, target);
                
        n=(int) me->query_skill("zuoyou-hubo", 1) /60;
		if (n>5) n=5;
        count= (int)me->query_skill("suxin-jian", 1)+ (int)me->query_skill("quanzhen-jian", 1)+ (int)me->query_skill("zuoyou-hubo", 1);
        count=count/3;
        
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count * 2 / 3);

        for (i = 0; i < n; i++)
        {
            if (! me->is_fighting(target))
                 break;
            
            if (random(2) && ! target->is_busy())
                        target->start_busy(1);
            
            COMBAT_D->do_attack(me, target, weapon1, 0);        
            weapon1->move(me, 1);
            weapon2->wield();
            me->map_skill("sword","quanzhen-jian");
            COMBAT_D->do_attack(me, target, weapon2, 0);
            weapon2->move(me, 1);
            weapon1->wield();
            me->set_temp("handing", weapon2);
            me->map_skill("sword","suxin-jian");
        }
        
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count * 2 / 3);
        me->add("neili", -n*70);
        me->start_busy(1 + random(7));
               
        return 1;
}
