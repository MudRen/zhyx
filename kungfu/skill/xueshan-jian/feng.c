// feng.c

#include <ansi.h>
#include <combat.h>

#define FENG "��" HIW "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;
        int ap, dp, count,i,n;
        int damage;
		string parry_str;
			

        if (userp(me) && ! me->query("can_perform/xueshan-jian/feng"))
		{			
            return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
		}		
		count = me->query("can_perform/xueshan-jian/times");	
		
		if (count > 2000000) 
			count = 2000000;	

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FENG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" FENG "��\n");

        if (me->query_skill("force") < 240)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" FENG "��\n");

        if (me->query_skill("xueshan-jian", 1) < 160)
                return notify_fail("���ѩɽ������Ϊ����������ʩչ" FENG "��\n");

        if (me->query("neili") < 600)
                return notify_fail("�����������������ʩչ" FENG "��\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("��û�м���ѩɽ����������ʩչ" FENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "ֻ��$N" HIW "һ����Х������" + weapon->name() +
              HIW "������ֹ���ų�����⻪��������������������ϯ��"
              "$n" HIW "��ȥ��\n" NOR;
              
       	parry_str=target->query_skill_mapped("parry");
		
        ap = me->query_skill("sword",1);
        if (me->query_skill("shangqing-jian",1) >= 600)
        	ap = ap * 0.3 + ap;
		else if (me->query_skill("shangqing-jian",1) >= 400)
		    ap = ap * 0.2 + ap;
	    else ap = ap;
		
		if (me->query("reborn")){
			ap = ap * 0.2 + ap;
		}
		
        dp = target->query_skill("dodge",1);

        if (ap * 3 / 5  + random(ap) > dp)
        {
                damage = ap  + random(ap) + count / 100;
                me->add("neili", -200);
			    me->add("can_perform/xueshan-jian/times", 1);
                me->start_busy(2);

				if (count > 500000)
				{
					  me->add("neili", -400);				      
                      target->receive_wound("qi", damage, me);
	        	      str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	                  msg += HIR "$n" HIR "ֻ�к���Ϯ�壬��δ����" HIR "$N" HIR "���еĳ����Ǻ�ʱ���ʵģ�ֻ�����ʺ�һ������Ѫ�罦������\n"	NOR;
				      msg += "($n"+str+")\n";
				}
				else
				{
                      msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,100,
                                           HIR "$n" HIR "ֻ�к���Ϯ�壬ȫ��һ���"
                                           "�����ѱ�$N" HIR "�������ˡ���ʱ����һ"
                                           "�����һ�����Ѫ��\n" NOR);
				}

				      if (count<2000000)
				      msg += HIC "$N" HIC"��ѩɽ����" HIW "÷�������ͽ������" HIC "�������µ�����\n" NOR;
        } else
        {
                me->add("neili", -50);
                me->start_busy(2);
                msg += CYN "����$n" CYN "����" CYN "$N" CYN
                       "������������Ծ���������ڽ���������"
                       "���������Ρ�\n"NOR;
        }
        
       message_combatd(msg, me, target);
       
      
       if (me->query("reborn"))
       	{       		
          message_combatd(HIW "������$N" HIW "����" + weapon->name() + 
        	       HIW "������ֻ�����ǵ�㣬������ʵ��ʵ����"
                     "�飬����˷���$n" HIW "��ȥ��\n" NOR, me, target);
               me->add_temp("apply/attack", 100);
               for (i = 0; i < 6; i++)
              {
                if (! me->is_fighting(target))
                        break;
				        if (random(2)==1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
				 me->add("neili", -80);		
              }
              me->add_temp("apply/attack", -100);	       			
               me->start_busy(2+random(4));
               
       	}       
       
        

        return 1;
}
