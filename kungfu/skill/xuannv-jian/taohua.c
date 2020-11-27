#include <ansi.h>
#include <combat.h>

#define TAOHUA "��" HIR "�����һ���" NOR "��"

inherit F_SSERVER;

string final1(object me, object target, int damage);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage);
string final4(object me, object target, int damage);
string final5(object me, object target, int damage);



int perform(object me, object target)
{
        object weapon;
        string wn, msg;       
        int ap, dp, damage, lvl;

        if (userp(me) && ! me->query("can_perform/xuannv-jian/taohua"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TAOHUA "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( me->query("int") < 25 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" TAOHUA "��\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("����ڹ���Ϊ����������ʩչ" TAOHUA "��\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ����������ʩչ" TAOHUA "��\n");

        if ((int)me->query_skill("xuannv-jian", 1) < 300)
                return notify_fail("����Ů������򲻹�������ʩչ" TAOHUA "��\n");

        if (me->query_skill_mapped("sword") != "xuannv-jian")
                return notify_fail("��û�м�����Ů����������ʩչ" TAOHUA "��\n");

        if ((int)me->query("neili") < 600)
                return notify_fail("��������������������ʩչ" TAOHUA "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        message_combatd(HIM "$N" HIM "΢΢һЦ���������" + wn +
                        HIM "������������ת�����е�������\n" NOR, me, target);

       ap = me->query_skill("sword");
       damage = ap * 2 + random(ap);
       lvl = (int)me->query_skill("xuannv-jian", 1);


        // ��һ�У��Ƚ϶����м�

       dp = target->query_skill("parry");        

        message_vision(HIG "\n  ȥ����մ�����\n\n" NOR, me, target); 

        if (ap * 4/ 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final1, me, target, damage, weapon, lvl :));        

        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ��У��Ƚ϶����Ṧ

        dp = target->query_skill("dodge") ;        
        message_vision(HIM "\n    �����һ���ӳ��\n\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final2, me, target, damage, weapon, lvl :));              

        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����У��Ƚ϶����ڹ�
        dp = target->query_skill("force");  
      
        message_vision(HIY "\n      ���治֪�δ�ȥ\n\n" NOR, me, target); 
  
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final3, me, target, damage, weapon, lvl :));              

        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

	// �����У��Ƚ϶�����ѧ����
        dp = target->query_skill("martial-cognize", 1);        
        message_vision(HIC "\n        �һ�����Ц����\n\n" NOR, me, target);


        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10), (: final4, me, target, damage, weapon, lvl :));               
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����У��Ƚ϶��ֶ���д�֣�������Ҳ�Ƚ����
        dp = target->query_skill("literate", 1);        
        message_vision(HIW "\n          ��Ů����ԭ����\n\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10), (: final5, me, target, damage, weapon, lvl :));               
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        me->start_busy(3 + random(3));
        me->add("neili", -800 - random(200));
        return 1;
}

string final1(object me, object target, int damage)
{
        return HIR "$n" HIR "�м��Ի�����Ȼ���У���Ѫ���粻ֹ��\n" NOR;
}

string final2(object me, object target, int damage)
{
        return  HIR "$n" HIR "���������ѱ�$N���д��У��Ҳ����ԣ�\n" NOR;
}
string final3(object me, object target, int damage)
{
        return  HIR "$n" HIR "�ڹ����ã���ʱ��$N�������ˣ�\n" NOR;
}
string final4(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 6, me);
        target->receive_wound("jing", damage / 8, me);
        return  HIR "$n" HIR "������$N�к����У������ش���\n" NOR;
}
string final5(object me, object target, int damage)
{
        target->start_busy(3 + random(3));
        return  HIR "$n" HIR "��$N��Ӱ���Ի�Ŀ�ɿڴ����������ã�\n" NOR;
}