//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define DAIZONG "��" HIC "������" NOR "��"

inherit F_SSERVER;
string attack1(object me, object target, int damage);

int perform(object me, object target)
{           
		int ap, dp;
		int damage;
		string msg;
		object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DAIZONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
  

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" DAIZONG "��\n");


        if (me->query_skill("wuyue-shenjian", 1) < 250)
                return notify_fail("�����������Ϊ����������ʩչ" DAIZONG "��\n");

        if (me->query("neili") < 1000)
                return notify_fail("�����������������ʩչ" DAIZONG "��\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("��û�м��������񽣣�����ʩչ" DAIZONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");	
				
		if (target->query_temp("daizong"))
                return notify_fail("�Է������Ѿ������������ŵ������ɡ�\n");

              
		msg=HIM "\nֻ��$N" HIM "����"+weapon->name()+HIM"бָ���£�������ָ������ָ��������һ�����壬�ն���ȭ��"
			     HIM"�ֽ�Ĵָ������ζ�ʳָ��������ָȫչ���ƺ��ڽ���һ�ָ��ӵ����㣡\n" NOR;

        ap = me->query_skill("sword") + me->query("int") * 20;
		dp = target->query_skill("dodge") +  target->query("int") * 12; 
	
        if (ap * 3 / 4 + random(ap) > dp)
        {        	
           damage = ap*7 + random(ap*4);
           me->start_busy(1+random(3));
           me->add("neili", -500);
                
          msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   (: attack1, me, target, damage :));    
                        		
        } else
	      {
	       	msg = HIG "ֻ��$n" HIG "�������ţ�ֻ������һ�����Ͷ����$N"
	               HIG "��һ����\n"NOR;
	         me->start_busy(2+random(3));
           me->add("neili", -400);
	      }

		message_vision(msg, me, target);
	return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;
		object weapon = me->query_temp("weapon");

		msg = HIR "\n$N΢΢һЦ���������г����һ�գ�����" + weapon->name()+ HIR "����ʯ�����$n����Ҫ����\n"
			        HIR "ֻ�������͡�һ����$n�ѱ�����Ҫ����\n" NOR;           

        if (! target->query_temp("daizong"))
        {
                msg += HIM "$nֻ������֫��ľ����ͬ����Ǧһ�㣬����������\n" NOR;
	
                target->add_temp("apply/parry", -400);
                target->add_temp("apply/dodge", -400);
                target->set_temp("daizong", 1);
        }
        call_out("daizong_end", 10 + random(15), me, target);
        return msg;
}

void daizong_end(object me, object target)
{
        if (target && target->query_temp("never_juemie"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��������ɫ��"
                                        "��ת�죬�������ö��ˡ�\n" NOR, target);                       
                }                
                target->add_temp("apply/parry", 400);
                target->add_temp("apply/dodge", 400);
                target->delete_temp("daizong");
        }
        return;
}
