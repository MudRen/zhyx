//created by kasumi
#include <ansi.h>
#include <combat.h>

#define FENG "��" HIW "ǧ�����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon, weapon2;
        int i, count, damage;
        int ap, dp;       

		if (me->query_skill("daojian-guizhen", 1) < 350)
                return notify_fail("��ĵ�������ȼ�����������ʩչ" FENG "��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(FENG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword"
           && (string)weapon->query("skill_type") != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" FENG "��\n");

        type = weapon->query("skill_type");

        if (me->query_skill(type, 1) < 300)
                return notify_fail("���" + to_chinese(type) + "̫�"
                                   "����ʩչ" FENG "��\n");

        if (me->query_skill_mapped(type) != "daojian-guizhen")
                return notify_fail("��û�м����������棬����ʩչ" FENG "��\n");        

        if (me->query("neili") < 600)
                return notify_fail("�����ڵ���������������ʩչ" FENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        

		msg = HIM "$N" HIM "��ɫ���أ�����" + weapon->name() + HIM "�������ˣ�����˺�ѿ�������Χ��������ɱ�����¶��轵��\n"
			      "ƬƬ"HIW"ѩ��" HIM "Ʈ�䣬$n" HIM "�����ѣ�üë�������˱���"HIW"��˪"HIM"��\n"
				  HIM "$N" HIM "һ��ŭ�𣺡�ǧ�����......����\n"
				  HIM"ֻ��"+ weapon->name()+ HIM "Ю�������ѩ��������֮������" HIM"$n��" HIM "���Ϊ֮��ɫ��\n" + NOR;


        ap = me->query_skill("sword", 1) + me->query_skill("blade", 1);
        dp = target->query_skill("sword",1) + target->query_skill("blade",1);
		
		damage= ap * 3 + random(ap*2);

		if (ap * 2 / 3 + random(ap) > dp)
        {
			me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "$n" HIR "��Ȼ�������������ܣ�$N"
										   HIR "�ĺ�����ã��ʱ͸����룬������Ѫ���磬����������\n" NOR);
        } else
        {
			me->add("neili", -150);
                msg += CYN "$n" CYN "���Ʋ���˲������棬����100����¿������Ǳ�֮�������ձܹ�$P�����ɱ�С�\n" NOR;
        }
		 message_combatd(msg, me, target);

	    msg = HIW "$N" HIW "����δ������ʽ��Ȼ��������ޱȣ�һת�����Ȼ��������......\n" NOR;

        if (ap / 2 + random(ap * 2) > dp)
        {
                count = ap / 3;
                msg += HIR "$n" HIR "��$P" HIR "����Ѹ��֮����һʱ��֪����"
                       "�������ֵ���������������\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "��$p" HIY "����Ѹ��֮�������ѷ�������"
                       "æ��������С�ĵֵ���\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);
	
        me->add("neili", -300);
        me->add_temp("apply/attack", count);        
		me->set_temp("daojian-guizhen/max_pfm", 1);

		for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
				if (random(2)==1 && ! target->is_busy())
					target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

		me->add_temp("apply/attack", -count);
        me->delete_temp("daojian-guizhen/max_pfm");
        me->start_busy(2 + random(5));
       
        return 1;
}
