// zhua.c ��������צ
// created by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHUA "��" HIR "��������צ" NOR "��"

int perform(object me, object target)
{
	int damage;
	string  msg;         
    int ap, dp;
    

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(ZHUA "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if (me->query_temp("weapon"))
            return notify_fail(ZHUA "ֻ�ܿ���ʩչ��\n");

    if ((int)me->query_skill("jiuyin-shengong", 1) < 250)
		return notify_fail("��ľ����񹦻�������죬����ʹ��" ZHUA "��\n");
	                        
        if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ��" ZHUA "��\n");

        if (me->query_skill_prepared("claw") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" ZHUA "��\n");
       
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "΢΢һЦ�����ֳ�צ������ץ��$n"
	      HIY "��ҪѨ��\n" NOR;
	

        ap = me->query_skill("jiuyin-shengong", 1) * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

	if (ap * 2 / 3 + random(ap) > dp)
    {
		damage = ap * 5 + random(ap*2);
	    me->add("neili", -200);
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                   HIR "ֻ�������ꡱһ����$N" HIR "��ָ������$n" HIR "��Ҫ����$n"
                                   HIR "һ���ҽУ�Ѫ���岽��\n"  NOR);
	}
	else
	{
		 me->add("neili", -200);
         me->start_busy(3);
         msg += HIC "$n" HIC "���в��ã���æ��ͷ������$N"
                HIC "�ֱ��������죬��Ȼ������Ѹ���ޱȵ�ץ��$n��\n" NOR;
         dp = target->query_skill("dodge") + target->query_skill("martial-cognize", 1);
                if (ap * 2 / 3 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                                   HIR "$n" HIR "�����ϵ�$N" HIR
                                                   "������˱��У�������������ͷ��$P"
                                                   HIR "ץ�˸���Ѫ���졣\n" NOR);
                } else
                        msg += CYN "$n" CYN "�������룬���м�ƮȻ���ˣ���$N"
                               CYN "��һ���޹�������\n" NOR;
	}
	message_combatd(msg, me, target);

	return 1;
}
