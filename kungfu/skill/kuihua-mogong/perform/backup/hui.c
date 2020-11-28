#include <ansi.h>
#include <combat.h>

#define HUI "��" HIR "��"BLU"��"HIM"��"HIW"��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
    int skill = (int)me->query_skill("kuihua-mogong", 1), i;
    string msg;
    int ap, dp;
    int damage;

    if( !target || target == me ) target = offensive_target(me);
    if( environment(me)->query("no_fight") )
	return notify_fail("���ﲻ׼��ܡ�\n");
    if( !target || target==me || !target->is_character() )
	return notify_fail(HUI"ֻ�ܶԶ���ʹ�á�\n");
    if (userp(me) && ! me->query("can_perform/kuihua-mogong/hui"))
	return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
    if (skill < 200 || (int)me->query_skill("kuihua-mogong", 1) < 200)
	return notify_fail("����Ŀǰ����Ϊ������������������"HUI"\n");
    if (me->query("max_neili") < 2000)
	return notify_fail("���������Ϊ��������"HUI"���裡\n");
    if (me->query("neili") < 500)
	return notify_fail("���������������"HUI"���裡\n");

    me->start_busy(1 + random(3));
    msg = "$N��ʼʹ�ÿ���ħ�����ռ�����----"HUI "\n"HIW"$N����ӨȻ�й⣬�ƺ�������ħ��֮�С�\n";

    if (me->query("can_perform/kuihua-mogong/miedi")){

	msg += "$nаа�Ŀ���$N����֪������$n���ֳ���ֵĿ־塣\n"NOR;
	msg += HIM"\n$N��Ȼ�뵽��ʲô��$n���̿�ʼ����ʹ�������������\n\n"NOR;

	ap = me->query_skill("kuihua-mogong", 1) * 3 + me->query("dex") * 20 +
	me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query("dex") * 20 +
	target->query_skill("martial-cognize", 1);

	me->start_busy(2);
	me->add("neili", -400);

	if (ap / 2 + random(ap) < dp)
	{
	    msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
	    "�Ĺ���һһ���⡣\n" NOR;
	} else
	{
	    me->add("neili",-560);
	    damage = ap * 2 + random(ap * 3 / 4) - 60 - random(40);
	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
	      HIY "$n" BLU "ֻ�����Ѿ����������ħ��֮�У�"HIY"$N"
	      WHT "��ͬ��������һ�������㵸���ӾžŰ�ʮһ����λɱ�˹�ȥ��\n" NOR);
	}

	message_combatd(msg, me, target);

    } else {
	msg += "$nаа�Ŀ���$N����֪������$n���ֳ���ֵĿ־塣\n"NOR;
	msg += HIM"\n$N��Ȼ�뵽��ʲô��$n���̿�ʼ����ʹ�������������\n\n"NOR;

	ap = me->query_skill("kuihua-mogong", 1) * 1 + me->query("dex") * 10 +
	me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query("dex") * 20 +
	target->query_skill("martial-cognize", 1);

	me->start_busy(2);
	me->add("neili", -400);

	if (ap / 2 + random(ap) < dp)
	{
	    msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
	    "�Ĺ���һһ���⡣\n" NOR;
	} else
	{
	    me->add("neili",-260);
	    damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
	      HIY "$n" BLU "ֻ�����Ѿ����������ħ��֮�У�"HIY"$N"
	      WHT "��ͬ��������һ�������㵸���ӾžŰ�ʮһ����λɱ�˹�ȥ��\n" NOR);
	}

	message_combatd(msg, me, target);

    }
    if(!me->is_fighting(target)) me->fight_ob(target);
    if(!target->is_fighting(me)) target->fight_ob(me);
    remove_call_out("checking");
    call_out("checking", 1, me);
    return 1;
}



