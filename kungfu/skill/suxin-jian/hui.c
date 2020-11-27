#include <ansi.h>
#include <combat.h>

#define HUI "��" HIW "��"HIY"��"HIW"��"HIR"��" NOR "��"

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

	if (userp(me) && ! me->query("can_perform/suxin-jian/hui"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query("gender") == "����")
                return notify_fail("���в��ʺ�����ʹ�ã�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" HUI "��\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ���Ϊ����������ʩչ" HUI "��\n");

        if ((int)me->query("max_neili") < 4500)
                return notify_fail("���������Ϊ����������ʩչ" HUI "��\n");

        if ((int)me->query_skill("suxin-jian", 1) < 350)
                return notify_fail("����Ů���Ľ�����򲻹�������ʩչ" HUI "��\n");

	if ((int)me->query_skill("yunv-xinjing", 1) < 300)
                return notify_fail("����Ů�ľ���򲻹�������ʩչ" HUI "��\n");

	/* if(me->query_temp("no_hui"))
                return notify_fail("����Ϣδ�ȣ��޷�ʹ��" HUI "��\n");      */

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail("��û�м�����Ů���Ľ���������ʩչ" HUI "��\n");

	if ((string)me->query_skill_mapped("force") != "yunv-xinjing")
                return notify_fail("����뼤����Ů�ľ�����ʩչ��" HUI "��\n");

        if ((int)me->query("neili") < 1200)
                return notify_fail("��������������������ʩչ" HUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	wn = weapon->name();
	lvl = (int)me->query_skill("suxin-jian", 1);

        message_combatd(HIW "$N" HIW "����һԾ��"HIW"$n"HIW"�������г��������ͦ����Ȼ���ϣ����˴�Լ��Ʈ���ޱȣ�\n"
                        HIW "��Ȼ��������Ů�ľ����һ�µľ�ѧ��\n" NOR, me, target);

	

	ap = me->query_skill("sword") + me->query_per() * 15;
	if (me->query_temp("wang") && target->query("gender") == "����")
		ap = ap * 1.5;	
	if (target->query("family/family_name") == "ȫ����")
       ap = ap * 1.75;	
	dp = target->query_skill("dodge") + target->query_per() * 15;   

        // ��һ��           

	message_vision(HIW"\n  ����"HIY"��"HIW"��"HIR"��"HIW"�� ֮" HIG"  �����޺� \n" NOR, me, target); 

	if (ap * 2/3 + random(ap) > dp)
	{
	    damage = ap + random(ap/2);
		msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
		20 + random(30),(: final1, me, target, damage, weapon, lvl :));        
	} else
	{
               msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

	// �ڶ���

	message_vision(HIW"\n    ����"HIY"��"HIW"��"HIR"��"HIW"�� ֮" HIW"  Ʈ����� \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{
	        damage = ap + random(ap/2);
               msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
               20 + random(40),(: final2, me, target, damage, weapon, lvl :));        

	} else
        {
               msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

	// ������

	message_vision(HIW"\n      ����"HIY"��"HIW"��"HIR"��"HIW"�� ֮" HIC"  ˪�䳤�� \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{
	  damage = ap + random(ap/2);
               msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,
               25 + random(50),(: final3, me, target, damage, weapon, lvl :));
	} else
	{
               msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
	}
        message_vision(msg, me, target);

	// ������

	message_vision(HIW"\n        ����"HIY"��"HIW"��"HIR"��"HIW"�� ֮" HIM"  �������� \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{ 
	       damage = ap + random(ap/2);
	       msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
	       25 + random(60),(: final4, me, target, damage, weapon, lvl :));        
	} else
	{
               msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
	}
	message_vision(msg, me, target);

	// ������

	message_vision(HIW"\n          ����"HIY"��"HIW"��"HIR"��"HIW"�� ֮" HIY"  ����׷�� \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{
	      damage = ap + random(ap/2);
	       msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
	       30 + random(70),(: final5, me, target, damage, weapon, lvl :));        
	} else
	{
	       msg = CYN "����$n" CYN "�������񣬷�����"
	              "�ܣ�������ж�����Ρ�\n" NOR;
	}
	message_vision(msg, me, target);

	/* call_out("hui_ok", 1 + random(2), me);     */
	me->start_busy(2 + random(4));
	me->add("neili", -1000);
	//me->set_temp("no_hui",1);
	
	return 1;
}

/* void hui_ok(object me)
{
	if (!me) return;
	me->delete_temp("no_hui");
} */

string final1(object me, object target, int damage)
{
        return HIG " $n" HIG "�����������������貨���ӵ�" HIG"$N" HIG"����ȫ��ȴ�˶�����\n" NOR;
}

string final2(object me, object target, int damage)
{
        return HIG " $n" HIG "һƳ" HIG"$N" HIG"���������ˣ�����������\n" NOR;
}

string final3(object me, object target, int damage)
{
        return HIG " $n" HIG "����" HIG"$N" HIG"�����ɵ��ĳ��񵴣��겻���ᣡ\n" NOR;
}

string final4(object me, object target, int damage)
{
        return HIG " $n" HIG "�Բ��λ࣬�޵����ݣ����������ٳ���\n" NOR;
}

string final5(object me, object target, int damage)
{
        return HIG " $n" HIG "��̾һ�����������磬˳�����𳤽������Լ�����Ĩȥ��\n" NOR;
}