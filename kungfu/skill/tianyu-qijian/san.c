// san.c  ��Ůɢ��

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, sp, dp, i;
        string result, str, msg;

        damage =  (int)me->query_skill("force");
        damage += (int)me->query_skill("sword");

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("����Ůɢ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
                
        if( (int)me->query_skill("tianyu-qijian", 1) < 100 )
                return notify_fail("��������潣������죬����ʹ�á�\n");

        if ( me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("��û�м��������潣�������ϣ�\n"); 

        if ((int)me->query_skill("bahuang-gong", 1)<200)
                return notify_fail("��İ˻�����Ψ�Ҷ��𹦻�򲻹���\n");

        if (me->query_skill_mapped("force") != "bahuang-gong")
                return notify_fail("��û�����ð˻�����Ψ�Ҷ��𹦹���\n");       

        if( (int)me->query("neili", 1) < damage + 200 )
                return notify_fail("����������̫��������ʹ�á���Ůɢ������\n");
                        
        message_vision(CYN "\n$N����Ϣ�������󼲶������ǧ�������������ǵط���$n��\n"NOR, me,target);

        me->add_temp("apply/attack",damage/10);
        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->add_temp("apply/attack",-damage/10);

        if (! me->is_fighting(target) )
        {
                me->add("neili",-100);
                me->start_busy(1 + random(3));
                return 1;
        }

        sp = me->query_skill("sword") + me->query_skill("dodge") + me->query_str() * 10;
        dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
        sp += me->query("jiali");
        if( sp/2 + random(sp) > dp || !living(target))
        {
                damage += random(damage/2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili",-damage/2);
                message_vision(HIR "\nֻ��$N������Ϊһ�ߣ�����$n��\n$nֻ��һ���������Ķ�������ͷһ����Ѫ���������\n\n" NOR, me,target);

                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                target->start_busy(1+random(2));
                me->start_busy(2);
        } else 
        {
                message_vision(CYN "$n���Ʋ����͵����һԾ,������$N�Ĺ�����Χ��\n"NOR, me,target);
                me->add("neili", -200);
                me->start_busy(4);
        }
        return 1;
}

