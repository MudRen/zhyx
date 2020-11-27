// you.c ��ڤһ��
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
       object weapon;
	     string msg;
	     int ap, dp;
       int damage;
       

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ڤһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("kuihua-mogong", 1) < 120)
		return notify_fail("��Ŀ���ħ����������죬����ʹ����ڤһ����\n");

       if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("�㻹û�м�������ħ��Ϊ�ڹ����޷�ʩչ��ڤһ����\n");  

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin")
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ��ڤһ����\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ��ڤһ����\n");
        }

        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ��ڤһ����\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ��ڤһ����\n");

        if (me->query("neili") < 200)
                return notify_fail("�����������������ʹ����ڤһ����\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
  
       ap = me->query_skill("dodge") + me->query("dex") * 20 + me->query_skill("unarmed");
	     dp = target->query_skill("dodge") + target->query("dex") * 10 + target->query_skill("unarmed");
  
       if (me->query_temp("weapon"))
  		       msg = HIR "$N" HIR "��������ǰȥ����ʱ��ƽ�$n" HIR"����������" + weapon->name() + HIR"��Ȼ����$p��Ҫ����\n" NOR;
  		 else   	
	           msg = HIR "$N" HIR "��������ǰȥ����ʱ��ƽ�$n" HIR"������������Ȼ����$p��Ҫ����\n" NOR;
 
	       

        if (ap / 2 + random(ap) < dp)
        {
		       msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG "�Ĺ���һһ���⡣\n" NOR;
		       me->add("neili",-80);
		       me->start_busy(1);  
        } else        	
	      {		
           damage = ap  + random(ap / 2) + random(100);
           if (me->query_temp("weapon"))
           {
           	msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "��æ���ˣ�������ң��������$N"
                                           HIR "���У���Ѫ����һ�أ�\n" NOR);
           }else
           {
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "��æ���ˣ�������ң��������$N"
                                           HIR "���У���Ѫ����һ�أ�\n" NOR);	
           }
           me->add("neili",-100);
           me->start_busy(1);  
	 }

	message_combatd(msg, me, target);
	return 1;
}
