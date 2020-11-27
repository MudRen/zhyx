// linglong.c ������

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
                return notify_fail("�������硹ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("���á������硹���б����н���\n");

        if ((int)me->query_skill("liudaolunhui-sword", 1) < 200)
                return notify_fail("��������ֻؽ���������죬����ʹ�á������硹��\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫��������ʹ�á������硹��\n");
                        
        msg = HIW "\n$N" HIW "��Ӱ�����ĸ�����$n" HIW "��ǰ��ֻ��$N" HIW "����������Ө��͸��"
              "������Χ����$n" HIW "��Χ��\n���⽣Ӱ��������ʱ�����������͵�ѩ��֮�У�"
              "��һ����������������\n\n" HIM "����ɽˮ�䣬���������!\n\n" NOR;

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

                msg += HIW "$n" HIW "��ʱ����������һ��ľ���֮�У���������б�ѩ���������!\n"
                       "$n" HIW "��ȫ���������������֮���޷��԰Ρ�\n���Ž����ǰ�Ĵ���" NOR;
                
                if (objectp(weapon2 = target->query_temp("weapon")))
                {
                        msg += HIW "������" + weapon2->name() + HIW "���һ�����ڵ��ϡ�\n" NOR;
                        weapon2->move(environment(target));
                }
                else
                        msg += HIW "��\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIY "��$n" HIY "��û�б���Ѥ����ѩ��������,��Ȼ������ѩ������Ļþ��У�\n" NOR;

                me->add("neili", -100);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
