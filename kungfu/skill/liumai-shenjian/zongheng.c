#include <ansi.h>
#include <combat.h>

#define ZONGHENG "��" HIY "�����ݺ�" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg, wp;
        int skill;        
        int damage;       
        int ap, dp, pp, p, str, aa, ab, ac;
        object weapon;

        if (! target) target = offensive_target(me);
        	   

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONGHENG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" ZONGHENG "��\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 800)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" ZONGHENG "��\n");

        if (me->query_skill("force") < 1200)
                return notify_fail("����ڹ���򲻹�������ʩչ" ZONGHENG "��\n");

        if (me->query("max_neili") < 12000)
                return notify_fail("���������Ϊû�дﵽ�Ǹ����硣\n");

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷����˾��У�\n");   

        if (me->query("neili") < 1000)
                return notify_fail("������������������޷�ʩչ" ZONGHENG "��\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ" ZONGHENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "̯��˫�֣���ָ��������ʱ��������ȣ���"
              "�����ڣ���������������Ѩ��һ�����$n" HIW "��\n\n" NOR;   

                pp = (int)me->query_skill("buddhism", 1) + (int)me->query_skill("lamaism", 1);

		  damage = (int)me->query_skill("finger",1)/2 + (int)me->query_skill("liumai-shenjian",1) * (int)me->query_skill("jingluo-xue", 1) / 350;
               
                damage += pp/2;
      

       

       // ��һ��
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("parry",1) + target->query_skill("jingluo-xue", 1);

	    msg += HIM "$N" HIM "˫��Ĵָͬʱ����������������죬��"+ HIY "���̽�"+ HIM "������ʯ���쾪�����������\n" NOR ; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "�����ֵ���ȴ�����мܵ�ס����$N"
                                           HIR "��һָ������Ѫ������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }

        // �ڶ���
	 ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("parry",1)+ target->query_skill("jingluo-xue", 1);

	    msg += HIY "����" HIY "$N" HIY "Ĵָһ����ʳָ�漴����������������죬���������������" HIR "������" HIY "������̳���\n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "��ͼ�ֵ���ֻ�����һ����"
                                           HIR "���ν�����������룬͸�������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һָ�㿪��˿������\n" NOR;
        }

        //// ������
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("dodge",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIG "ֻ��" HIG "$N" HIG "������ָһ������" HIC "�г彣" HIG "����ǰ�̳��������ĵ�����Ȼ���죬���ν���ֱָ$n�� \n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "һ㶣�ֻ��������һ����"
                                           HIR "�ѱ�����������Ѫ�ɽ���\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }

        //// ������
	 ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("dodge",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIC "$N" HIC "����ָ����һ�ӣ���������һ����׾�͹��ӵġ�" MAG "�س彣" HIC "��������" HIC"$n" HIC"ֱ�������\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "������������������ڴ��Ѫ������"
                                           HIR "��Ѫ��ӿ������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "�������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }
      

        //// ������
	 ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/5;
        dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIB "����$N" HIB "����Сָһ�죬һ���������ٳ�Ѩ�м��������һ�ɡ�" HIW "����" HIB "����ʱ����$n��\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "�����ֵ���ֻ����һ��͸������"
                                           "Ϯ��������һ�����裬�������̱�ÿտյ�����\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һָ��\n" NOR;
        }
		//// ������
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/5;
        dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIW "���"HIW "$N" HIW"����Сָһ�ӣ�һ�С�" HIG "�ٳ彣" HIW "�����̴��ƿմ̳�������񻨴̻�һ�㡣\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "��Ȼ�����ֿ�����ƾ������Ϯ"
                                           "ֻ����һ��������....\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "�����ֵ������ڽ�����$N"
                       CYN "��һָ�������Ǳ�������\n" NOR;
        }              


     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("liumai-shenjian", 1) > 799 && !userp(target))
        	 {
                  ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/2;
                  dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);
                  aa = me->query_skill("kurong-changong",1);
                  ab = me->query_skill("kurong-changong",1);
                  ac = me->query_skill("kurong-changong",1);

        msg += HIC "\n$N" HIC "һ��񹥣���������֮�ʣ���������������ɱ����\n"
               HIM "$N" HIM "�پ�����������ӿ����ͷ������˷������಻������ʱ�����籼�������޾������������Ȼ������\n"
               HIY"��������������ǿ�����������ݺ᡹,����Ѹ�׼����໥��ײ��֮�ʣ�\n"
               HIW"��Ȼ�㼯��һ��������ƥ�Ľ���������һ����ɫ����,����㼲����$n������\n" NOR;
       
		 if (ap * 3 / 4 + random(ap) > dp)
                {
                damage = (int)me->query_skill("finger", 1)/2 + (int)me->query_skill("liumai-shenjian", 1) + (int)me->query_skill("jingluo-xue", 1)*5;               
                damage += pp;
                damage += aa*2;
                damage += ab*2;
                damage += ac*5;
                damage = damage + random(damage);
                target->receive_damage("qi", damage*2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "���޿ɱܣ�ֻ����ƾ������Ϯ������������\n" NOR;
	        	str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	msg += "($n"+str+")\n";
                if (objectp(weapon = target->query_temp("weapon"))
                   && weapon->query("stable", 1) < 100
                   && ap + random(ap) > dp)
                  {
                        wp = weapon->name();
                        msg += HIW "ֻ�����ϡ���һ�����죬$n" HIW "��"
                               "�е�" + wp + HIW "��$N" HIW "��������"
                               "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR;
                        me->add("neili", -150);
                        weapon->set("consistence", 0);
                        weapon->move(environment(target));
                 }

                } 
                 else
                      {
                msg += CYN "$n" CYN "�����ֵ������ڽ�����$N"
                       CYN "��һָ�������Ǳ�������\n" NOR;
                      }  
           }   

	    message_combatd(msg, me, target);
	    me->add("neili", -1800);
        me->start_busy(2 + random(4));

        return 1;
}

