// jiubu.c �Ų�ʽ

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
		return notify_fail("���Ų�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("���Ų�ʽ��ֻ�ܿ���ʹ�á�\n"); 

	if ((int)me->query_skill("zhemei-shou", 1) < 120)
		return notify_fail("�����÷�ַ�������죬����ʹ�á��Ų�ʽ����\n");
	                        
	if ((int)me->query_skill("xiaowuxiang", 1)<150
		&& (int)me->query_skill("lingjiu-xinfa", 1)<150
		&& (int)me->query_skill("xiaoyao-xinfa", 1)<150
		&& (int)me->query_skill("bahuang-gong", 1)<150
		&& (int)me->query_skill("beiming-shengong", 1)<150)
        return notify_fail("��������ڹ��ķ�����ȷ�����߹�������������ʹ�þ��У�\n");

	if ( me->query_skill_mapped("force") != "xiaowuxiang"
		&& me->query_skill_mapped("force") != "bahuang-gong"
		&& me->query_skill_mapped("force") != "lingjiu-xinfa"
		&& me->query_skill_mapped("force") != "xiaoyao-xinfa"
		&& me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("��û��������ң��ϵ���ڹ���\n");	
			
	if ((int)me->query("neili") < 100)
		return notify_fail("��������������������ʹ�á��Ų�ʽ����\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("��û�м�����ɽ��÷�֣�����ʹ�á��Ų�ʽ����\n");

	msg = HIC "$N" HIC "˫������ʵʵ��ץ��$n"
              HIC "��Ҫ��������翣���ʽ���أ���������׽����\n" NOR;

        ap = me->query_skill("hand") + me->query_str()*10;
	ap += me->query("jiali")*2/3;
        dp = target->query_skill("dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp || !living(target))
	{
                damage = me->query_skill("hand") + me->query_skill("force");
                damage += random(damage/2);
		me->add("neili", -damage/10);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
		                           HIR "$p" HIR "һ�����ܲ����������$P"
                                           HIR "ץ�˸����У�������Ϣ���ɵ�һ�ͣ���Ѫ��ӿ��\n" NOR);
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
                                           HIM "��÷���л����ǿ���İ˻�����Ψ�Ҷ��𹦾�����\nδ�����֮�£�ǿ�����Ϣ�������壬�����ſڿ���һ����Ѫ��\n" NOR);
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
                                       HIM + "��÷���л��ʹ���˱�ڤ�񹦣�\nδ�����֮�£�����������й����������������ɫ��\n" NOR;
			}
		}
		target->start_busy(1+random(2));
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�������ݣ�����Ķ����$P"
                       HIC "�Ĺ�����\n"NOR;
		me->add("neili", -50);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
