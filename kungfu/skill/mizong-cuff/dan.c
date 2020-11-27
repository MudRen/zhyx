// dan.c ��ն

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("����ն��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if(me->query_skill_mapped("cuff") != "mizong-cuff") 
                return notify_fail("��û��������ȭ���޷�ʹ�á���ն�����У�\n");

        if (me->query_skill_prepared("cuff") != "mizong-cuff")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ����ն�����С�\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ���Ʒ����С�\n");

        if ((int)me->query_skill("mizong-cuff", 1) < 200)
                return notify_fail("�������ȭ������죬����ʹ�á���ն����\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫��������ʹ�á���ն����\n");
                        
        msg = HIR "\n$N" HIR "ͻȻ�Ƶ�$n" HIR "���˫ȭ�͵Ļ���$n" HIR "�ĺ�����\n" NOR;

        ap = me->query_skill("cuff") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");
        
        damage = ap*2 + random(ap);
        damage += me->query("jiali");

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2 = target->query_temp("weapon");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -damage/2);

                msg += HIR "ֻ�������ꡱһ�����죡$n" HIR "���һ����Ѫ���������ĵ�����ȥ��\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                msg += HIB "��֪$n" HIB "�������׼��������һչ�����׵Ļ��������У�\n" NOR;

                me->add("neili", -100);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
