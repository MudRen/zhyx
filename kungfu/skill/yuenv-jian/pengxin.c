// pengxin.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
        int damage;
        int delta;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
	        return notify_fail("���������ġ�ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
	        return notify_fail("��ʹ�õ��������ԡ�\n");

        if (userp(me) && ! me->query("can_perform/yuenv-jian/pengxin"))
                return notify_fail("�㲻��ʹ�á��������ġ���һ������\n");

	if (me->query_dex() < 35)
		return notify_fail("�����������Ŀǰ������ʹ�����������\n");

	if (me->query_skill("sword", 1) < 100)
		return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�á��������ġ���\n");

	if (me->query_skill("yuenv-jian", 1) < 100)
		return notify_fail("���ԽŮ��������Ϊ����������ʹ����һ������\n");

	if (me->query_skill("dodge") < 150)
		return notify_fail("����Ṧ��Ϊ�������޷�ʹ�á��������ġ���\n");
 
	if (me->query("neili") < 200)
		return notify_fail("�������������\n");

        if (me->query("gender") == "Ů��" &&
            target->query("gender") == "Ů��")
                delta = target->query("per") - me->query("per");
        else
                delta = 0;

	msg = HIG "$N" HIG "����һ����̾�����е�" + weapon->name() +
              HIG "������������$n���ؿڡ�\n" NOR;
        if (delta > 0)
                msg += HIY "$n" HIY "ֻ����$N" HIY "��������Ȼ͸��"
                       "һ�ɱ���ĺ��⣬���в���һ����\n" NOR;
        else
                delta = 0;

	me->add("neili", -150);
        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");
        me->start_busy(1);
        if (ap /2 + random(ap) + me->query("per") > dp || !living(target))
        {
                damage = ap / 2 + random(ap / 2) + delta * 50;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
                                           HIR "$n" HIR "���һ������æ��ܣ�Ȼ����"
                                           "�����ĺÿ죬�����ÿ���\nֻ��$p" HIR
                                           "һ���ҽУ��ؿ��Ѿ����������ˣ�\n" NOR);
                if (ap / 4 + random(ap) > dp)
                {
                        damage /= 2;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                   HIC "$n�ش�֮�²�������������$P"
                                                   HIC "��״���ִ̳�" + weapon->name() +
                                                   HIC "������һ����\n" HIR "����$p"
                                                   HIR "����һ���ҽУ�ʹ�಻����\n" NOR);
                }
        } else
        {
                msg += HIC "$n" HIC "��״���μ��ˣ��ܿ���$N"
                       HIC "�����ν���������һ����\n" NOR;
        }

        message_combatd(msg, me, target);

	return 1;
}
