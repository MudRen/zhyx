// jinglei.c ��ָ����
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

string final(object me, object target, int ap, int dp, int wound);
 
int perform(object me)
{
	string msg;
	object weapon, target;
        int skill, ap, dp, damage, fi;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ָ���ס�ֻ����ս���жԶ���ʹ�á�\n");

	skill = me->query_skill("tanzhi-shentong", 1);

	if (skill < 120)
		return notify_fail("��ĵ�ָ��ͨ�ȼ�����, ����ʹ�á���ָ���ס���\n");

	if (me->query("neili") < 250)
		return notify_fail("��������������޷����á���ָ���ס���\n");
 
	if (me->query_skill_mapped("finger") != "tanzhi-shentong") 
		return notify_fail("��û�м�����ָ��ͨ���޷�ʹ�á���ָ���ס���\n");

	msg = HIC "$N" HIC "ʹ����ָ��֮ͨ����ָ���ס�����ʱ"
	      "���ھ��Ⱪ�䣬һ������ָ����Ϯ��$n" HIC "��\n" NOR;
 
        fi = me->query_skill("tanzhi-shentong");
	ap = me->query_skill("finger") + me->query_skill("force");
	dp = target->query_skill("dodge") +
	     target->query_skill("parry");
        if (ap + random(fi) > dp || !living(target))
	{
		me->add("neili", -200);
		damage = ap / 3 + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           (: final, me, target, ap, dp, damage :));
		me->start_busy(3);
                target->start_busy(1 + random(3));
	} else
	{
		msg += CYN "����$p" CYN "�Ŀ�����$P" CYN "����ͼ�����̲�ȡ"
		       "���ƣ�ʹ$P" CYN "�ġ���ָ���ס�û�������á�\n" NOR;
		me->add("neili", -50);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target, int ap, int dp, int wound)
{
        object weapon;
        string msg;

        msg = HIR "$p" HIR "ֻ������ǰɱ���ݺᣬ����"
              "��ʧɫ�����ܲ�����ֻ����"
	      "����Ѩ��һ���ʹ���������ʣ�\n" NOR;
        if ((weapon = target->query_temp("weapon")) &&
            ap / 4 + random(ap) > dp)
        {
		target->receive_damage("jing", wound / 3, me);
		target->receive_wound("jing",  wound / 8, me);
		msg += HIR "$p" HIR "����һ�飬����" + weapon->name() +
		       HIR "�������ֶ�����\n" NOR;
		weapon->move(environment(me));
        }
        return msg;
}
