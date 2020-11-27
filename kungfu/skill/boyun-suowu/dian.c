#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        
        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (userp(me) && ! me->query("can_perform/boyun-suowu/dian")) 
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ�������㡹��\n"); 
                    
        if( me->query_temp("weapon") )
                return notify_fail("�����ϲ���װ���κζ�����\n");

        if (! me->is_fighting(target)) 
                return notify_fail("ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 

        if( (int)me->query_skill("boyun-suowu", 1) < 100 )
                return notify_fail("��ġ���������������죬����ʹ�á������㡹��\n");

        if( (int)me->query_skill("biyun-xinfa",1) < 100)
                return notify_fail("����ķ�����������\n");

        if( (int)me->query("neili") < 800 ) 
                return notify_fail("�������������\n");

        ap = attack_power(me, "hand") + me->query_dex();
        dp = defense_power(target, "dodge") + target->query_dex();

        msg = HIG "$N����һ��������һ���黨�����������£����͡���һ�����ƿն�ȥ!\n"NOR;

        message_vision(msg, me, target);

        me->add("neili", -500);
        
        if (ap / 2 + random(ap) > dp)        
        {
                if (! target->is_busy())
                        target->start_busy( 2 + (int)me->query("hand")/50);
                msg = HIC "$nȫ��پ�һ�飬�ƺ����ܶ�����\n"NOR;
        }  
        else 
                msg = HIM "ֻ��$n����һ�ã�һ��������ƿն�����\n"NOR;  
        message_vision(msg, me, target);
        
        return 1;
}


