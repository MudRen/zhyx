// dan.c ����

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
                return notify_fail("�����¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("���á����¡����б����н���\n");

        if ((int)me->query_skill("canyue-sword", 1) < 200)
                return notify_fail("��Ĳ��½���������죬����ʹ�á����¡���\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫��������ʹ�á����¡���\n");
                        
        msg = WHT "\n$N" WHT "�����Ȼ����������𶯡����Ȿ����ббָ��$n" WHT "����һ�������Ȼ��ȫ����ֹ��\n"
              "������Χ�Ŀ��������ݷ�Ҳ��ͣ�١�\n" WHT "û���κ���������������������ֻ��һ���֣�һ���ܼ򵥵���...\n\n"
              HIR "���� \n\n" HIB "��ˮǬ�ݣ��仯��������սᣬ����������\n\n" NOR; 

        ap = me->query_skill("sword") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");
        
        damage = ap*2 + random(ap);
        damage += me->query("jiali");

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -damage/2);

                msg += HIR "$N" HIR "���е�" + weapon->name() + HIR "�ƺ����ѹ�����$n������ȴ�������ţ�һ�����޷��ٸı䡣 \n" NOR;
                
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIR "$N" HIR "һ��ʧȥĿ�꣬��Ȼ�������·𱻳���" + weapon->name() + RED "��Ҳ�޷����ƣ�"
                       + weapon->name() + HIR "������ֶ�����\n" NOR; 

                me->add("neili", -100);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
