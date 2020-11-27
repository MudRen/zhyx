#include <ansi.h>
#include <combat.h>

#define JIUZHOU "��" HIY "���޳���" NOR "��"
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, i, count;
        string msg, sub_msg;
        int ap, dp;
        object weapon;       
        int lvl;

        if (userp(me) && ! me->query("can_perform/tianzi-jian/jiuzhou"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIUZHOU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JIUZHOU "��\n");   
        if (me->query_skill_mapped("sword") != "tianzi-jian")
                return notify_fail("��û�м������ӽ���������ʩչ" JIUZHOU "��\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("��������Ϊ����������ʩչ" JIUZHOU "��\n");

        lvl = (int)me->query_skill("tianzi-jian", 1);
        if (lvl < 250)
                return notify_fail("�����ӽ�����򲻹�������ʩչ" JIUZHOU "��\n");

        if ( me->query("int") < 15 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");   

        if ((int)me->query("neili") < 800)
                return notify_fail("��������������������ʩչ" JIUZHOU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_sort(HIY "\n$N" HIY "ͻ�Ե���̬֮�������ߺ���\n\n"NOR
                     HIR"  ����֮�£�Ī�����������ӽ��������޳�����\n\n"NOR
                     HIW "     ������������ƺ�����ǧ��������ͬ$N" HIW"�Ľ��о���Ϯ��$n"
                     "��\n\n" NOR, me, target);

        weapon = me->query_temp("weapon");

       //���ӽ������й���
        msg = HIG "\nֻ��$N" HIG "������������������벻��֮����"
              "$n" HIG"ֱ�̹������������ֳ����߰�����\n" NOR;
 
        ap = me->query_skill("tianzi-jian", 1) * 2 +              
             me->query_skill("martial-cognize", 1);

        dp = target->query_skill("parry", 1) +
             target->query_skill("martial-cognize", 1);

        me->add("neili", -150);

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;	         
        } else
        {
                me->add("neili", -200);	        
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           HIR "$n" HIR "��æ�����ܣ�Ȼ����һ�����ù���"
                                          "��ֻ��$n" HIR "һ���ҽУ���һ���Ѵ���$n��" HIR "��"
                                          "ʱ��Ѫ�ɽ���\n" NOR); 
        }
        message_sort(msg, me, target);

       //�ٳ��Ž�(������ + һ����)
       if (! me->is_fighting(target) ) return 1;

        msg = HIY "������$N" HIY "������ʩ���Ž������дӲ�ͬ��λ����$n" HIY"Ҫ����\n" NOR; 

       
        count = ap / 8;        

        me->add_temp("apply/attack", count);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, i * 2);
        }
        me->add_temp("apply/attack", -count);

       if ( ! me->is_fighting(target) ) return 1;

       
        if (ap * 4 / 5 + random(ap) > dp)
        {       
                damage = ap + random(ap);
                target->receive_damage("qi", damage * 2 / 3 , me);
                target->receive_wound("qi", damage * 2 / 3, me);
                msg += HIR "���һ���������棬$n" HIR 
                      "���޿ɱܣ��ձ����У������ش���\n" NOR;
        } else
        {
                msg += HIC "����$n" HIC "��ǰԤ������ǿ�㿪$N" HIC"������һ����\n" NOR;
        }
        message_combatd(msg, me, target);
        me->add("neili", - ( 400 + random(50)) ); 
        me->start_busy(3 + random(2));
        return 1;
}
