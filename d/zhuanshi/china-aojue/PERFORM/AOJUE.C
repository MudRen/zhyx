#include <ansi.h>
#include <combat.h>

#define AOJUE "��" HIR "�л�����" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string wn, msg;       
        int ap, dp, damage, lvl, idle, i, count;

        if (userp(me) && ! me->query("can_perform/china-aojue/aojue"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(AOJUE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( me->query("int") < 15 ) 
                return notify_fail("����������Բ��㣬�޷�ʹ�ô��С�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" AOJUE "��\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("����ڹ���Ϊ����������ʩչ" AOJUE "��\n");

        if ((int)me->query("max_neili") < 6000)
                return notify_fail("���������Ϊ����������ʩչ" AOJUE "��\n");

        if ((int)me->query_skill("china-aojue", 1) < 300)
                return notify_fail("���л�������򲻹�������ʩչ" AOJUE "��\n");

        if ((int)me->query_skill("idle-force", 1) < 300)
                return notify_fail("�㷢���񹦵ȼ�����������ʩչ" AOJUE "��\n");

        if (me->query_skill_mapped("sword") != "china-aojue")
                return notify_fail("��û�м����л�����Ϊ����������ʩչ" AOJUE "��\n");

        if (me->query_skill_mapped("force") != "china-aojue")
                return notify_fail("��û�м����л�����Ϊ�ڹ�������ʩչ" AOJUE "��\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("��������������������ʩչ" AOJUE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        message_combatd(HIM "$N" HIM "΢΢һЦ���������" + wn +
                        HIM "������������ת�����е�������\n" NOR, me, target);
      
       lvl = (int)me->query_skill("china-aojue", 1);
       idle = (int)me->query_skill("idle-force", 1);

        // ��һ�У����ֹ���һ������
       if ( me->query_skill_mapped("strike") == "china-aojue" &&
            me->query_skill_prepared("strike") == "china-aojue" )
       {
           ap = me->query_skill("strike") + me->query_skill("martial-cognize");
           damage = ap + random(ap);
           dp = target->query_skill("parry") + target->query_skill("dodge");        
 
           message_vision(HIG "\n  ȥ����մ�����\n\n" NOR, me, target); 

           if (ap * 4/ 5 + random(ap) > dp)
           {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 
                120 + random(10));        

            } else
            {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
             }
            message_vision(msg, me, target);
        }

        // �ڶ��У����������Ž�

        ap = me->query_skill("sword") + me->query_skill("martial-cognize");
        damage = ap + random(ap);
        dp = target->query_skill("parry") + target->query_skill("dodge");        

        message_vision(HIM "\n    �����һ���ӳ��\n\n" NOR, me, target);

        count = lvl / 9;

        if (count > 60 ) count = 60;

        me->add_temp("apply/attack", count);
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, i * 4 );
        }
        me->add_temp("apply/attack", -count);


        // �����У�����һ�����У��жϷ�����
        ap = me->query_skill("sword") + me->query_skill("martial-cognize", 1);
        damage = ap + random(ap);
        dp = target->query_skill("parry") + target->query_skill("dodge");        
        message_vision(HIY "\n      ���治֪�δ�ȥ\n\n" NOR, me, target); 
  
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
                90 + random(10),(: final, me, target, damage, weapon, lvl :));              

        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);


        me->start_busy(3 + random(2));
        me->add("neili", -600 - random(200));
        return 1;
}


string final(object me, object target, int damage)
{
        return  HIR "$n" HIR "���������ѱ�$N���д��У��Ҳ����ԣ�\n" NOR;
}

