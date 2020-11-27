// dan.c �����޻�

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
                return notify_fail("�������޻ڡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if(me->query_skill_mapped("cuff") != "mingyu-cuff") 
                return notify_fail("��û��������ȭ���޷�ʹ�á������޻ڡ����У�\n");

        if (me->query_skill_prepared("cuff") != "mingyu-cuff")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ�������޻ڡ����С�\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ���Ʒ����С�\n");

        if ((int)me->query_skill("mingyu-cuff", 1) < 200)
                return notify_fail("�������ȭ������죬����ʹ�á������޻ڡ���\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫��������ʹ�á������޻ڡ���\n");
                        
        msg = HIB "\n$N" HIB "��ȫ��������˫ȭ��һ����ȣ�ƽƽ����$n�Ƴ�˫�ƣ�\n" NOR;

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
        
        if (ap / 3 + random(ap/2) > dp)
        {
                damage += damage/2;
                me->add("neili", -damage/2);

                msg += HIR "\nֻ����ž��һ�����죬$N" HIR "��˫ȭ�Ѿ�����ʵʵ�Ĵ���$n" HIR "�����ˣ�\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else if (ap / 2 + random(ap) > dp)
        {
                damage += damage/2;
                me->add("neili", -damage/2);

                if (weapon2)
                {
                        msg += HIM "\n$n" HIM "���޿ɱܣ�ֻ�þ������е�" NOR + weapon2->name() + HIM "Ӳ��һ�С�\n"
                               HIM "ֻ����ž����һ����$n" HIM "��" NOR + weapon2->name() + HIM "�Ѿ���������ء�\n" NOR;
                        if (ap / 3 + random(ap) > dp)
                        {
                                damage -= damage/3;
                                msg += HIM "$N" HIM "ȭ�ƶٵ�һ�٣�ȴ��Ȼ���صش�����$n" HIM "���ϡ�\n" NOR;
                        } else
                        {
                                damage -= damage/2;
                                msg += HIM "$n" HIM "��Ȼ��������ϣ�ȴҲ���˿������˻��ܿ���\n" NOR;
                        }
			weapon2->set_name("���ѵ�" + weapon2->query("name"));
                        weapon2->move(environment(target));
			weapon2->set("value", 0);
			weapon2->set("weapon_prop", 0);
			target->reset_action();
                } else
                {
                        msg += HIG "\n$n" HIG "���޿ɱܣ�ֻ��Ҳͬ��˫ȭƽ��Ӳ��һ�С�\n"
                               HIG "һ�����춯�صؾ��죬˫ȭ�ཻ֮�£�$n" HIG "�������Ѫ��ӿ��\n" NOR;
                        if (ap / 2 + random(ap) > dp)
                        {
                               msg += HIG "$N" HIG "��ȭ��˿������Ӱ�죬��Ȼ���صĴ�����$n" HIG "�����ϣ�\n" NOR;
                        } else if (ap / 2 + random(ap*2) > dp)
                        {
                               msg += HIG "$n" HIG "��Ȼ������$N" HIG "������һ����ȴ��Ȼ��ȭ�����ˣ�ֻ��һ����Ϣ��\n" NOR;
                               damage -= damage/3;
                        } else
                        {
                               msg += HIG "����ȭ���ཻ֮�£�$N" HIG "��ȫ��һ������ȫ���⡣\n" NOR;
                               damage -= damage; 
                        }

                }               
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else
        {
                if (weapon2)
                        msg += HIY "$n" HIY "��������ǧ��֮��������Ӷ�" NOR + weapon2->name() + HIY "���㲦����$N" HIY "��"HIR"�����޻ڡ�\n" NOR;
                else
                        msg += HIY "$n" HIY "��������ǧ��֮����������֣��㲦����$N" HIY "��"HIR"�����޻ڡ�\n" NOR;

                me->add("neili", -100);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
