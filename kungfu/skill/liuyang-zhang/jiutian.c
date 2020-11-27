// jiutian.c ����ʽ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp, ap1, dp1;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("��ɽ������ֻ�п��ֲ��ܹ�ʹ�ã�\n");

	if ((int)me->query_skill("liuyang-zhang", 1) < 120)
		return notify_fail("��������Ʒ�������죬����ʹ�á�����ʽ����\n");
	                        
        if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ�����ߣ��������á�����ʽ����\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á�����ʽ����\n");
			
	msg = HIC "$N" HIC "˫��һ�񣬻���������Ӱ����������ס$n" HIC "��\n" NOR;

        ap = me->query_skill("force") + me->query_str()*10;
	ap += me->query("jiali")*2/3;
        dp = target->query_skill("force") + me->query_dex()*10;

        if (ap / 2 + random(ap) > dp || !living(target))
	{
		damage = me->query_skill("strike") + ap - dp;
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$p" HIR "���Σ�ֻ��Ӳ��һ�У������$P"
                                           HIR "���������������Ѫ��ֹ��\n" NOR);

		if (me->query_skill_mapped("force") == "bahuang-gong")
		{
			ap1 = me->query_skill("force");
			ap1 += me->query("jiali");
			ap1 += random(ap1/2);
			dp1 = target->query_skill("force");
			dp1 += target->query("jiali");
			dp1 += random(dp1/2);
			if (ap1 > dp1)
			{
		                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, ap1, 60,
		                           HIM "$p" HIM "��δ���ü�������Ϣ���������$P"
                                           HIM "�������л����ǿ���İ˻�����Ψ�Ҷ��𹦾�����\nδ�����֮�£�ǿ�����Ϣ�������壬�����ſڿ���һ����Ѫ��\n" NOR);
			}
		}
		if (me->query_skill_mapped("force") == "beiming-shengong")
		{
			ap1 = me->query_skill("force");
			ap1 += me->query("jiali");
			ap1 += random(ap1/2);
			dp1 = target->query_skill("force");
			dp1 += target->query("jiali");
			dp1 += random(dp1/2);
			if (ap1 > dp1)
			{
                                target->add("neili",-ap1*2);
				if (target->query("neili") < 0)
					target->set("neili",0);
		                msg += HIM + target->name() + HIM + "��δ���ü�������Ϣ���������" + me->name() +
                                       HIM + "�������л��ʹ���˱�ڤ�񹦣�\nδ�����֮�£�����������й����������������ɫ��\n" NOR;
			}
		}
                me->add("neili",-200);
		target->start_busy(1+random(2));
		me->start_busy(2+random(2));
	} else
	{
		msg += HIC "����$p" HIC "ǿ��������Ӳ�����ĵ�ס$P"
                       HIC "��һ�ƣ�û���ܵ��κ��˺���\n"NOR;
		me->add("neili", -50);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
