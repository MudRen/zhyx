//zhou.c
//smallbear 11/1/2002

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        object target;
        int skill, ap, dp, attack_decrease,dodge_decrease;
        
        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("busi-shenlong",1) + me->query_skill("force",1);
        
        if( !me->is_fighting() )
                return notify_fail("���䷨��ֻ����ս����ʹ�á�\n");
        if( (int)me->query_skill("busi-shenlong", 1) < 200)
                return notify_fail(HIM "��Ĳ��������ķ���Ϊ���㣬���޷��������������! \n" NOR);
        if( (int)me->query("neili") < 1000 || (int)me->query("max_neili")<2000  ) 
                return notify_fail("��������������޷�������ԡ�\n");
                
        message_vision(HIR "\n$NͻȻ���һԾ��˫��������չ���������д�......\n
                       ���겻��!�����ɸ�!��������!������ʥ��\n
                       ���겻��!�����ɸ�!��������!������ʥ��\n
                       ���겻��!�����ɸ�!��������!������ʥ��\n\n" NOR, me);
        
        ap = me->query("combat_exp") + skill * 500;
        if(living(target))
             dp = target->query("combat_exp") / 4;
        else   dp = 0;

        if( random(ap) > dp )
        {
                if(userp(me))
                        me->add("neili",-500);
                msg = HIR "$n����$N���е����ͻ�о����㱣��ֽŶ�ʱ����ʹ����\n"NOR;
                attack_decrease = (int)target->query("apply/attack") / 10;
                dodge_decrease = (int)target->query("apply/dodge") / 10;
                target->add_temp("apply/attack", -attack_decrease);
                target->add_temp("apply/dodge", -dodge_decrease);
                target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                msg = CYN "$n�۹۱ǣ��ǹ��ģ���Ԫ��һ������������а����ƣ�\n"NOR;
                if(userp(me))
                        me->add("neili",-500);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
