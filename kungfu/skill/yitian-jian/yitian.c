// yitian.c 倚天决

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        int extra,i,time;
        string msg;
        i = me->query_skill("yitian-jian", 1);
        time = 5;
         if( !target ) target = offensive_target(me);

        if( !me->is_fighting() )
                return notify_fail("「倚天决」只能在战斗中使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("「倚天决」开始时必须拿着一把剑！\n");
        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("你没有激发倚天剑法，怎么使用「倚天决」啊!\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内功修为不够！\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够！\n");

        if( (int)me->query_skill("yitian-jian",1) < 120 )
                return notify_fail("你的倚天剑还不到家，无法使用「倚天决」！\n");

        msg =HIY "$N" HIY "长啸一声：\n" HIR "武林至尊、宝刀屠龙。号令天下，莫敢不从。倚天不出，谁与争锋? \n"
             HIR "顿时风云变色，" HIR "$N" HIR "手中舞出漫天剑光........ \n" NOR;

        message_vision(msg, me);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", i/2);
//        for(i=1;i<=(int)time;i++)
        {
        msg =  HIC "-----拔云见日!----- \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg =  BLU "-----星河在天!----- \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg =  HIY "-----倚天不出!----- \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg =  HIR "-----谁与争锋!----- \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg =  HIM "-----号令天下!----- \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
        }
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/damage", -i/2);
        me->add("neili",-200);
        me->start_busy(4);
        return 1;
}

