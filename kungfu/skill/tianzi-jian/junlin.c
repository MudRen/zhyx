//junlin.c ��������--���ӽ��ռ�����

#include <ansi.h>
#include <combat.h>

#define JUNLIN "��" HIY "��������" NOR "��"
inherit F_SSERVER;


string final2(object me, object target, int damage, int lvl);
string final3(object me, object target, int damage, int lvl);
string final5(object me, object target, int damage, int lvl);

int perform(object me, object target)
{
        int damage, i, count;
        string msg, sub_msg;
        int ap, dp;
        object weapon;       
        int lvl;

        if (userp(me) && ! me->query("can_perform/tianzi-jian/junlin"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUNLIN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JUNLIN "��\n");   
        if (me->query_skill_mapped("sword") != "tianzi-jian")
                return notify_fail("��û�м������ӽ���������ʩչ" JUNLIN "��\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("��������Ϊ����������ʩչ" JUNLIN "��\n");

        lvl = (int)me->query_skill("tianzi-jian", 1);
        if (lvl < 300)
                return notify_fail("�����ӽ�����򲻹�������ʩչ" JUNLIN "��\n");

        if ( me->query("int") < 25 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");   

        if ((int)me->query("neili") < 1500)
                return notify_fail("��������������������ʩչ" JUNLIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");       

        message_sort(HIY "\n$N" HIY "�����������ӣ�ʢŭ֮�»���������Ȼ͸����"
                     "���и�ɢ�������������������������¡��ľ��跢�ӵ����쾡�£�"
                     "��ʽ����ԴԴ���ϵ���$n" HIY"ӿ����\n\n"NOR, me, target);

        weapon = me->query_temp("weapon");


        ap = me->query_skill("tianzi-jian", 1)  +              
             me->query_skill("martial-cognize", 1);
        damage = ap + random(ap);


       //��һʽ����Ծ������������
        msg = HIG "\nֻ��$N" HIG "ʩ�����������¡���һʽ����Ծ������������������"
              + weapon->name() + HIG"���类���������е���������������������צֱ�ɾ���"
              "֮�ϡ�\n\n" NOR; 

        dp = target->query_skill("parry", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           HIR "$n" HIR "��æ�����ܣ�Ȼ����һ�����ù���"
                                          "��ֻ��$n" HIR "һ���ҽУ���һ���ѽ�$n" HIR "�̵�"
                                          "��Ѫ�ɽ���\n" NOR); 
 
        }
        message_sort(msg, me, target);

       //�ڶ�ʽ���������·��Ʊ䡹     
        msg = HIY "\n$N" HIY "ʩ�����������¡��ڶ�ʽ���������·��Ʊ䡹"
              "�����г���������ֱ����$n" HIY"���أ����о����������������۽���֮�ϣ�"
              "������Ϊ���У�\n\n" NOR;   
        dp = target->query_skill("dodge", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70 + random(5),
                                           (: final2, me, target, damage, lvl :));
        }
        message_sort(msg, me, target);

    
       //����ʽ������ǧɽ��������

        msg = HIW "\n$N" HIW "ʩ�����������¡�����ʽ������ǧɽ��������"
              "�����ƻ���һͷ�׶��ͻ���ŭ�˶��ϣ���$n" HIW"�������ɣ�����$n" 
              HIW"��ȥ��\n\n" NOR;   
        dp = target->query_skill("force", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                          (: final3, me, target, damage, lvl :));

        }
        message_sort(msg, me, target);

       //����ʽ������һŭ�����

        msg = HIC "\n$N" HIC "ʩ�����������¡�����ʽ������һŭ�����"
              "�����ƻ���һͷ�׶��ͻ���ŭ�˶��ϣ��ƺ�Ҫ��$n" HIC"���������ɣ�\n\n" NOR;   

        dp = target->query_skill("literate", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;	         
        } else
        {
               
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           HIR "$n" HIR "��æ�����ܣ�Ȼ����һ�����ù���"
                                          "��ֻ��$n" HIR "һ���ҽУ���һ���ѽ�$n" HIR "�̵�"
                                          "��Ѫ�ɽ���\n" NOR); 
        }
        message_sort(msg, me, target);

       //����ʽ������������Ǭ����

        msg = HIR "\n$N" HIR "ʩ�����������¡�����ʽ������������Ǭ������"
              "������ɭ����â�������һ���޴�����У���ؼ��ƺ�ȼ�������һ�" 
              "����֮�ڸ��Ǵ������Ȼ𾢣�$n" HIR"�����������ڣ�������⣡\n\n" NOR; 

       
        dp = target->query_skill("martial-cognize", 1) * 2;     

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;	         
        } else
        {               
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           (: final5, me, target, damage, lvl :));

        }
        message_sort(msg, me, target);

        me->add("neili", - ( 1200 + random(300)) ); 
        me->start_busy(2 + random(3));
        return 1;
}

string final2(object me, object target, int damage,int lvl)
{
        target->add("neili", -(lvl + random(lvl)));

        return  HIR "$n" HIR "ֻ��$N" HIR "�����Ӱ������ͱ��ˣ���Ȼ�����ֵ�������$N����"
                "���������ˣ�$n" HIR 
                "�ƺ�һ���������ѱ����У��پ���Ϣ���в�����������Ȼ��ɢ��\n" NOR;
}

string final3(object me, object target, int damage, int lvl)
{       
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "�ۼ�����ֻ�ͻ����Լ���������ʱ����һ����"
                "ֻ��������ɢ��ȫ�����ơ�\n" NOR;
}

string final5(object me, object target, int damage, int lvl)
{       
        target->start_busy(4 + random(lvl / 40));
        return  HIR "$n" HIR "�����������֮�࣬һʱ����޻���֮����"
                "������ԭ�ض������ã�\n" NOR;
}

