#include <ansi.h>
#include <combat.h>

#define XIAN "��" HIM "�����������ɽ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg,str;
        object weapon;
        int ap, dp, fp, pp;


        if (! target) target = offensive_target(me);
		
				if(me->query_temp("no_daizong"))
                return notify_fail("������ʹ�þ��������Σ�\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if ((int)me->query_skill("zixia-shengong", 1) < 300)
                return notify_fail("����ϼ�񹦲�����죬����ʩչ" XIAN "��\n");

        if ((int)me->query_skill("wuyue-shenjian", 1) < 300)
                return notify_fail("�������񽣲�����죬�޷�ʩչ" XIAN "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�����������������޷�ʩչ" XIAN "��\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("��û�м��������񽣣��޷�ʹ��" XIAN "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -600);

        ap = me->query_skill("wuyue-shenjian", 1) + me->query_skill("zixia-shengong", 1) + me->query_skill("sword", 1);
        dp = target->query_skill("dodge", 1) + target->query_skill("force");

        if (me->query_skill("wuyue-shenjian", 1) > 799 && me->query("reborn"))
        {
                ap += ap / 5;
        }

		if (me->query_skill("zixia-shengong", 1) > 400 && me->query_skill_mapped("force") == "zixia-shengong"){
		
			message_sort(HIW "\n$N" HIW "����������ʢ������" + weapon->name() + HIW "�漴��ͣת������ӿ��"
                        "�������������񽣾�����" HIM "�����������ɽ�" HIW "��������" + weapon->name() + HIW 
                        "����ͻ�䣬һ����ʱ��Ϊ������Ϯ��$n" HIW "����\n" NOR, me, target);        

			msg = HIM "$N" HIM "����ϼ�ڹ�ȫ���������ϣ�����һ������ͷֱ����\n" NOR;
			if (ap * 2 / 3 + random(ap) > dp)
			{
              damage = ap*2 + random(ap);
              target->receive_damage("qi", damage, me);
              target->receive_wound("qi", damage/2, me);
              msg +=  HIR "$n" HIR "��æ���ˣ���Ȼ��ܲ�������$N"HIR "��һ����ÿ�����Ѫ���������ˡ�\n" NOR;
              str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	  msg += "($n"+str+")\n";

			} else
			{
                msg += CYN "$n" CYN "б��������\n" NOR;
			}
			message_combatd(msg, me, target);

  
			msg = HIM "\n$N" HIM "Ȧת" + weapon->name() + HIM "���������������ƻֺ룬�����ݺᣬ���˷�����˼��\n" NOR;
       
			if (ap * 2 / 3 + random(ap) > dp)
			{       
                damage = ap * 2 + random(ap*2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                msg += HIR "�������Ƶ���켰��$n" HIR "�������ü���"
							"���мܣ�ֻ��$N" HIR "����������$n"HIR "������ʱ��Ѫ���죡\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	msg += "($n"+str+")\n";
			} else
			{
              msg += CYN "$n" CYN "����ӽ���Խ����\n" NOR;
			}
			message_combatd(msg, me, target);
    
			msg = HIM "\n$N" HIM "�������ã�����$p" HIM "���ģ�����֮�죬��λ֮׼����������δ�š�\n" NOR;

			if (ap * 3 / 4 + random(ap) > dp)
			{
                damage = ap * 3 + random(ap*2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage, me);
                msg +=  HIR "$n" HIR "���ڿ��У��������ü����У�ֻ��$N"
                                 HIR "�˽��ӹ���$n" HIR "�����Һ�����Ѫ���·ɽ���\n" NOR;
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
				msg += "($n"+str+")\n";
			} else
			{
                msg += CYN "$n" CYN "���ڿ��У��������У�ֻ�ܻӳ�һ�У�������$N"
                       CYN "���ϣ���һ������ƮȻ��ȥ��\n" NOR;
			}
			message_combatd(msg, me, target);
			me->start_busy(3+random(2));
		}else{
		
			message_sort(HIW "\n$N" HIW "��Хһ��������" + weapon->name() + HIW "�漴��ͣת������ӿ��"
                        "�������������񽣾�����" HIM "�����������ɽ�" HIW "��������" + weapon->name() + HIW 
                        "����ͻ�䣬һ����ʱ��Ϊ������Ϯ��$n" HIW "����\n" NOR, me, target);        

			msg = HIM "$N" HIM "������ȫ���˵��˽��ϣ�����һ������ͷֱ����\n" NOR;

                damage = ap*2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(10),
                                           HIR "$n" HIR "��æ���ˣ���Ȼ��ܲ�������$N"
                                           HIR "��һ����ÿ�����Ѫ���������ˡ�\n" NOR);
        

			msg += HIM "\n$N" HIM "Ȧת" + weapon->name() + HIM "���������������ƻֺ룬�����ݺᣬ���˷�����˼��\n" NOR;

                damage = ap*2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(20),
                                           HIR "�������Ƶ���켰��$n" HIR "�������ü���"
                                           "���мܣ�ֻ��$N" HIR "����������$n"
                                           HIR "������ʱ��Ѫ���죡\n" NOR);
        

			msg += HIM "\n$N" HIM "�������ã�����$p" HIM "���ģ�����֮�죬��λ֮׼����������δ�š�\n" NOR;

                damage = ap*2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(30),
                                           HIR "$n" HIR "���ڿ��У��������ü����У�ֻ��$N"
                                           HIR "�˽��ӹ���$n" HIR "�����Һ�����Ѫ���·ɽ���\n" NOR);
        

			me->start_busy(3);
			message_combatd(msg, me, target);
		}
        return 1;
}
