// dan.c ˫��ָ

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
                return notify_fail("��˫��ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if(me->query_skill_mapped("finger") != "qiluo-finger") 
                return notify_fail("��û��������������޷�ʹ�á�˫��ָ�����У�\n");

        if (me->query_skill_prepared("finger") != "qiluo-finger")
                return notify_fail("��û��׼��ʹ������������޷�ʩչ��˫��ָ�����С�\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ��ָ�����С�\n");

        if ((int)me->query_skill("qiluo-finger", 1) < 200)
                return notify_fail("����������������죬����ʹ�á�˫��ָ����\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫��������ʹ�á�˫��ָ����\n");
                        
        msg = HIB "\n$N" HIB "����Ĭ��������˵���飬��Ȼ��ʽһ���������ˣ�������������֮�⡣\n"
              HIB "$n" HIB "��$N" HIB "���в��̣���Ҫ������ȴ��$N" HIB "�Ӵ����ŷ���˫�ֽ��ۣ�˫ָ��ת��ңָ$n�� \n"
              HIB "$n" HIB "һʱ������ţ���֪$N" HIB "�������У���ͷһ����㯡�\n"
              HIW " �� �� �� �� !\n"
              HIB "�����л�����ǿ����" HIB + to_chinese(me->query_skill_mapped("force"))+ HIB "��$n" HIB "����������ң�\n"
              HIB "ֻ�е��Է��˳�������ǧ�������������ϲ���������˷�ӿ������ʹЭ��˫�����Ǳ��޿ɱܣ�\n\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
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
                if (weapon2)
                {
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ�������" + weapon2->name() + HIM "�����Ӱ������ˮй��ͨ\n"
                               HIM "$N" HIM "�����������ţ�" HIW "��������" HIM "�Ծ����಻����$n" HIM "����" + weapon2->name() + HIM "����������֮�£�\n"
                               HIM "��Ϊ����Ķ���ʮ�أ����ϰ�գ��������ڹ⣡\n" NOR;
                                damage -= damage/3;
                                weapon2->set_name("���ѵ�" + weapon2->query("name"));
                                weapon2->move(environment(target));
                                weapon2->set("value", 0);
                                weapon2->set("weapon_prop", 0);
                                target->reset_action();
                } else
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ����������˫�Ʒ������$N��\n"
                               "$N" HIM "�����������ţ�" HIW "��������" HIM "�Ծ����಻����$n" HIM "�޿��κ�֮�£���ײ����Ѫ������\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                if (weapon2)
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ�������" + weapon2->name() + HIM "�����Ӱ������ˮй��ͨ\n"
                               "$N" HIM "������һ����" HIW "��������" HIM "��Ȼ���\n" NOR;
                else
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ����������˫�Ʒ������$N��\n"
                               HIM "$N" HIM "������һ����" HIW "��������" MAG "��Ȼ��գ���$n" HIM "Ҳ��$N" HIM "ײ����Ѫ��ӿ��\n" NOR;

                me->add("neili", -100);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
