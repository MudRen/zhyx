#include <ansi.h>
#include <combat.h>

#define SIX "��" HIY "��������" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill,delta,delta2;        
		int damage;       
        int ap, dp;

        if (! target) target = offensive_target(me);
        	
        if (userp(me) && ! me->query("can_perform/liumai-shenjian/six"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");        

        if (! target || ! me->is_fighting(target))
                return notify_fail(SIX "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" SIX "��\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 350)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" SIX "��\n");

        if (me->query_skill("force") < 400)
                return notify_fail("����ڹ���򲻹�������ʩչ" SIX "��\n");

        if (me->query("max_neili") < 7000)
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת��"
                                   "���γ�" SIX "��\n");

        if (me->query("neili") < 1000)
                return notify_fail("������������������޷�ʩչ" SIX "��\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ" SIX "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "̯��˫�֣���ָ��������ʱ��������ȣ���"
              "�����ڣ���������������Ѩ��һ�����$n" HIY "��\n\n" NOR;   

		  delta = (me->query_skill("jingluo-xue", 1) + me->query_skill("lamaism", 1)  + me->query_skill("buddhism", 1)) / 2;
		  delta2 =  (target->query_skill("jingluo-xue", 1) + target->query_skill("lamaism", 1)  + target->query_skill("buddhism", 1)) / 2;
		  damage = (int)me->query_skill("finger") + (int)me->query_skill("canhe-zhi", 1) + (int)me->query_skill("yiyang-zhi", 1) + delta;
		  damage = damage + random(damage/2);
			  
      

       

       //���̽�
        ap = me->query_skill("liumai-shenjian",1)+ delta;
        dp = target->query_skill("parry",1) + delta2;

	    msg += HIW "$N" HIW "˫��Ĵָͬʱ����������������죬��"+ HIY "���̽�"+ HIW "������ʯ���쾪�����������\n" NOR ; 
       
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

        // ������
        ap = me->query_skill("liumai-shenjian",1) + delta;
        dp = target->query_skill("parry",1)+ delta2;

	    msg += HIW "\n����" HIW "$N" HIW "Ĵָһ����ʳָ�漴������͵�һ�������������������" HIR "������" HIW "������̳���\n"NOR; 
       
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

        //�г彣
        ap = me->query_skill("liumai-shenjian",1)+delta;
        dp = target->query_skill("dodge",1)+delta2;

	    msg += HIW "\nֻ��" HIC "$N" HIW "������ָһ�㣬��" HIG "�г彣" HIW "����ǰ�̳��������ĵ�����Ȼ���죬���ν���ֱָ$n�� \n"NOR; 
       
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

        //�س彣
        ap = me->query_skill("liumai-shenjian",1)+delta;
        dp = target->query_skill("dodge",1)+delta2;

	    msg += HIW "\n$N" HIW "����ָ����һ�ӣ���������һ����׾�͹��ӵġ�" MAG "�س彣" HIW "��������" HIW"$n" HIW"ֱ�������\n"NOR; 
       
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
      

        //����
        ap = me->query_skill("liumai-shenjian",1)+ delta;
        dp = target->query_skill("force",1)+delta2;

	    msg += HIW "\n����$N" HIW "����Сָһ�죬һ���������ٳ�Ѩ�м��������һ�ɡ�" HIB "����" HIW "����ʱ����$n��\n"NOR; 
       
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
		//�ٳ彣
		ap = me->query_skill("liumai-shenjian",1)+ delta;
        dp = target->query_skill("force",1)+delta2;

	    msg += HIW "\n���"HIW "$N" HIW"����Сָһ�ӣ�һ�С�" HIC "�ٳ彣" HIW "�����̴��ƿմ̳�������񻨴̻�һ�㡣\n"NOR; 
       
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

		message_combatd(msg, me, target);
	    me->add("neili", -800);
        me->start_busy(3 + random(5));

        return 1;
}

