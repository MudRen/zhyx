// This program is a part of NITAN MudLIB
// meng.c �����Ρ�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/boyun-suowu/meng"))
                return notify_fail("�㻹����ʹ����һ�У�\n");
                
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�����Ρ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á����Ρ���\n");           

        if( (int)me->query_skill("boyun-suowu", 1) < 140 )
                return notify_fail("��Ĳ�����������죬����ʹ�á����Ρ���\n");

        if( (int)me->query_skill("biyun-xinfa", 1) < 130 )
                return notify_fail("��ı����ķ������ߣ��������������˵С�\n");

        if( (int)me->query("neili", 1) < 300 )
                return notify_fail("����������̫��������ʹ�á����Ρ���\n");

        msg = CYN "$NĬ��ھ���ʹ������������֮�����Ρ�����������������$n��\n"NOR;


        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)        
        {
                me->start_busy(3);
                //target->start_busy(random(3));
                
                damage = damage_power(me, "hand");
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/6);
                me->add("neili", -300);
                
                if( damage < 20 )
                        msg += HIY"���$n�ܵ�$N�����������ƺ�һ��������ȥ����ƣ����\n"NOR;
                else if( damage < 40 )
                        msg += HIY"���$n��$N����������ֻ�������з��ƣ�ֻ��ú���Ϣ��Ϣ��\n"NOR;
                else if( damage < 80 )
                        msg += RED"���$n��$N������һ�������������죬��ʶ��ʼģ��������\n"NOR;
                else
                        msg += HIR"���$n��$N������һ����ǰһ�ڣ����㵹���ۿ���Ҫ���������ˣ�\n"NOR;
                
        }
        else 
        {
                me->start_busy(2);
                msg += CYN"����$p������$P����ͼ����û���ϵ���\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}


