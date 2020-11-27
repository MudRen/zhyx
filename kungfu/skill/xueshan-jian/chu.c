#include <ansi.h>
#include <combat.h>

#define CHU "��" HIW "ѩ������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,msg1,parry_str;
        int ap, dp,damage;
        int count,count1;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/xueshan-jian/chu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" CHU "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" CHU "��\n");

        if (me->query_skill("xueshan-jian", 1) < 140)
                return notify_fail("���ѩɽ������Ϊ����������ʩչ" CHU "��\n");

        if (me->query("neili") < 200)
                return notify_fail("�����������������ʩչ" CHU "��\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("��û�м���ѩɽ����������ʩչ" CHU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
				
		parry_str=target->query_skill_mapped("parry");

        msg = HIW "$N" HIW "����" + weapon->name() + HIW
              "����������һ�С�ѩ����������������ʵ��ʵ����"
              "�飬����˷���$n" HIW "��ȥ��\n" NOR;
			  
		count1 = me->query("can_perform/xueshan-jian/times");

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");
        attack_time = 6;
		
		if ( count1 > 800000 && me->query("reborn")){
			//cancel parry
			target->map_skill("parry", 0);
			message_sort(msg, me, target);
			//һŪ
			msg1=HIM"  ÷��һŪ��" HIW "���˳���\n"NOR;		  
				damage = me->query_skill("sword");
				damage = damage + random(damage/2);
				msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��ǰһ����" HIR "���͡��ص�һ�������Ѿ�����һ��÷�����ε��˿ڣ�\n" NOR);	
				message_combatd(msg1, me, target);
			//��Ū
			msg1=HIM"    ÷����Ū��" HIG "��˼����\n"NOR;	
		  
				damage = me->query_skill("sword");
				damage = damage + random(damage/2);
				msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��ǰһ����" HIR "���͡��ص�һ�������Ѿ�����һ��÷�����ε��˿ڣ�\n" NOR);	
				message_combatd(msg1, me, target);
			//��Ū
			msg1=HIM"      ÷����Ū��" HIY "�粨��\n"NOR;	
		  
				damage = me->query_skill("sword");
				damage = damage + random(damage/2);
				msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��ǰһ����" HIR "���͡��ص�һ�������Ѿ�����һ��÷�����ε��˿ڣ�\n" NOR);	
				message_combatd(msg1, me, target);
			//��Ū
			msg1=HIM"         ÷����Ū��" HIC "�˱��㣡\n"NOR;
		  
				damage = me->query_skill("sword");
				damage = damage + random(damage/2);
				msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��ǰһ����" HIR "���͡��ص�һ�������Ѿ�����һ��÷�����ε��˿ڣ�\n" NOR);	
				message_combatd(msg1, me, target);
			//��Ū
			msg1=HIM"            ÷����Ū��" HIG "��տ�\n"NOR;
		  
				damage = me->query_skill("sword");
				damage = damage + random(damage/2);
				msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��ǰһ����" HIR "���͡��ص�һ�������Ѿ�����һ��÷�����ε��˿ڣ�\n" NOR);	
				message_combatd(msg1, me, target);
			//��Ū
			msg1=HIM"               ÷����Ū��" HIW "��������\n"NOR;
		  
				damage = me->query_skill("sword");
				damage = damage + random(damage/2);
				msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "��ǰһ����" HIR "���͡��ص�һ�������Ѿ�����һ��÷�����ε��˿ڣ�\n" NOR);	
				message_combatd(msg1, me, target);
				
			me->add("can_perform/xueshan-jian/times", 1);
			if (count1<2000000){
				msg = HIC "$N" HIC"��ѩɽ����" HIW "÷�������ͽ������" HIC "�������µ�����\n" NOR;
			}
			target->map_skill("parry", parry_str);
			message_combatd(msg, me, target);			
			me->start_busy(2+random(4));
			me->add("neili", -600);			
		}else{		
			if (ap / 2 + random(ap * 2) > dp)
			{
                msg += HIR "$n" HIR "ֻ����Ӱ���أ���ʱ�ۻ���"
                       "�ң������˸����ֲ�����ƣ�ڱ�����\n" NOR;
                count = ap / 8;
                
			} else
			{
                msg += HIC "$n" HIC "��$N" HIC "������ӿ����"
                       "��Ϯ�壬��æ���������С��Ӧ����\n"
                       NOR;
                count = 0;
			}
			message_combatd(msg, me, target);

			me->add_temp("apply/attack", count);
			me->add_temp("apply/damage", count / 2);
			me->add("neili", -attack_time * 20);

			for (i = 0; i < attack_time; i++)
			{
                if (! me->is_fighting(target))
                        break;
				if (random(3)==1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
			}

			me->add_temp("apply/attack", -count);
			me->add_temp("apply/damage", -count / 2);
			me->add("can_perform/xueshan-jian/times", 1);
			if (count1<2000000){
				msg = HIC "$N" HIC"��ѩɽ����" HIW "÷�������ͽ������" HIC "�������µ�����\n" NOR;
			}
			message_combatd(msg, me, target);
			me->start_busy(1 + random(attack_time));
		}
        return 1;
}
