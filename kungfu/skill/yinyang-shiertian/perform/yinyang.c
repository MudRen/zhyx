#include <ansi.h>
#include <combat.h>


#define YIN "��" HIR "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,name;
        int ap, dp;
        int damage;
	object equipment;

//        if (userp(me) && ! me->query("can_perform/yinyang-shiertian/yinyang"))
//                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YIN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(YIN "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("yinyang-shiertian", 1) < 300)
                return notify_fail("��������תʮ�������򲻹�������ʩչ" YIN "��\n");

        if (me->query_skill_mapped("force") != "yinyang-shiertian")
                return notify_fail("��û�м���������תʮ������Ϊ�ڹ�������ʩչ" YIN "��\n");

        if (me->query_skill_mapped("unarmed") != "yinyang-shiertian")
                return notify_fail("��û�м���������תʮ�����죬����ʩչ" YIN "��\n");

        if (me->query_skill_prepared("unarmed") != "yinyang-shiertian")
                return notify_fail("��û��׼��������תʮ�����죬����ʩչ" YIN "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" YIN "��\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("���������Ϊ����������ʩչ" YIN "��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�����ڵ��������㣬����ʩչ" YIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʩ��������תʮ�����������" HIR "��������"
		HIY "�������ֳ�צ������ץ��$n��ҪѨ��\n\n" NOR;     

//        ap = me->query_skill("strike") + me->query("str") * 10;
//        dp = target->query_skill("parry") + target->query("con") * 10;
//        dd = target->query_skill("dodge") + target->query("dex") * 10;

        ap = me->query_skill("yinyang-shiertian", 1) * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

	if (ap * 3 / 4 + random(ap) > dp)
        {
		damage = ap * 5 + random(ap * 2);
		me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
				HIR "ֻ�������ꡱһ����$N" HIR "��ָ������$n" HIR "��Ҫ����$n"
				HIR "һ���ҽУ�Ѫ���岽��\n"  NOR);
	}
	else
        {
		me->add("neili", -200);
		msg += HIC "$n" HIC "���в��ã���æ��ͷ������$N"
			HIC "�ֱ��������죬��Ȼ������Ѹ���ޱȵ�ץ��$n��\n" NOR;

		if (ap * 3 / 4 + random(ap) > dp)
                {
			damage = ap * 5 + random(ap * 2);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
					HIR "$n" HIR "�����ϵ�$N" HIR
					"������˱��У�������������ͷ��$P"
					HIR "ץ�˸���Ѫ���졣\n" NOR);
                } else
                        msg += CYN "$n" CYN "�������룬���м�ƮȻ���ˣ���$N"
                               CYN "��һ���޹�������\n" NOR;
        }

        msg += HIY "\n������$N" HIY "˫Ŀ΢�գ��������Ƶ������졣���Ķ�ʱ����һ���ޱȴ��۵����š�\n"
		"�漴$N" HIY "��£���ģ����ű��ѿ����������ܵ����������â���Ժ��������ԡ�\n" NOR;


        ap = me->query_skill("yinyang-shiertian", 1) * 3 / 2 + me->query_str() * 5;
        dp = target->query_skill("parry") + target->query_dex() * 5;

	if (ap * 3 / 4 + random(ap) > dp)
        {
		me->add("neili", -300);
                damage = ap * 5 + random(ap);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
				HIR "\n$n"HIR"��æ������ˣ���ֻ����ǰ��â���ǣ�һ��������"
				"ȫ���Ѷ��������˿ڣ���Ѫ�ɽ���\n" NOR);
		target->start_busy(2 + random(3));
        } else
        {
		me->add("neili", -200);
		msg += HIC "\n$n" HIC "ֻ����ǰ����������Χ�����������ڣ���֮����æ�����ڹ�������\n" NOR;

		if (ap * 3 / 4 + random(ap) > dp)
                {
			me->add("neili", -200);
                	damage = ap * 5 + random(ap);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
					HIR "Ȼ����â����ǧ��ϸ��һ������$n"HIR"�����ڡ�\n��â������"
					"$n"HIR"������Ѫ������Ť����ɷ�ǿֲ���\n" NOR);
			target->start_busy(2 + random(3));
                } else
		{
			me->add("neili", -100);
                        msg += CYN "ֻ����â������$n��������ס���У�" NOR;
			target->start_busy(3 + random(3));
			//�Ʒ���
			if (objectp(equipment = target->query_temp("armor/cloth")))
			{
				if (equipment->query("consistence") < 30)
				{
					name = equipment->name();
					equipment->set("consistence", 0);
					equipment->move(environment(me));
					msg +=CYN "Ȼ��$n���ŵ�" + name + HIC "�Ѿ����ս��ˡ�\n" NOR;
				}
				else
				{
					name = equipment->name();                                      
					equipment->add("consistence", -20);
					msg +=CYN "Ȼ��$n" CYN "���ϵ�" + name + CYN "ȴ�Ѿ����𲻿���\n" NOR;
				}
			}
			else
				msg +=CYN "Ȼ��$n" CYN "���ϵ��·����Ѿ�û���ˣ�\n" NOR;				
		}
        }
	message_combatd(msg, me, target);
        me->start_busy(1 + random(2));
        me->add("neili", -500);
        return 1;
}
