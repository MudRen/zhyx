// fumo.c Τ�з�ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
        int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail("��Τ�з�ħ��ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ��Τ�з�ħ����\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("weituo-gun", 1) < 135)
		return notify_fail("���Τ�ӹ�����Ϊ������Ŀǰ����ʹ��Τ�з�ħ��\n");

	if (me->query("neili") < 800)
		return notify_fail("�����������������ʹ��Τ�з�ħ��\n");

        if (me->query_skill_mapped("club") != "weituo-gun")
                return notify_fail("��û�м���Τ�ӹ���������ʹ��Τ�з�ħ��\n");

        if (me->query("shen") < 10000)
                return notify_fail("���������㣬�������Τ�з�ħ�ľ��衣\n");

	msg = HIY "$N" HIY "��ɫ��ͣ�����һ�ɴ���֮�⣬���е�" + weapon->name() +
              HIY "������������Գ����Τ������������䣬����ס$n" + HIY "��\n" NOR;

        if (target->is_bad())
        {
                ap = me->query("shen") / 1000;
                if (ap > 100) ap = (ap - 100) / 4 + 100;
                if (ap > 200) ap = (ap - 200) / 4 + 200;
                if (ap > 300) ap = (ap - 300) / 4 + 300;
                if (ap > 500) ap = 500;
                msg += HIR "$n" HIR "ƽ�������٣����˴���˾������в�����Ȼ��\n" NOR;
        } else
                ap = 0;
        ap += me->query_skill("staff"); 
        dp = target->query_skill("force");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = ap / 2 + random(ap / 2);
                me->add("neili", -500);
                me->start_busy(1);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "���ֻ��$p" HIR "һ���ҽУ���$P"
                                           "һ���Ӵ���Ҫ��������һ�����̣����Ƕ�����Ѫ����\n" NOR);
                target->start_busy(0);

        } else
        {
                me->add("neili", -60);
                me->start_busy(3);
                msg += CYN "����$p" CYN "ǿ������û�б�$P"
                       CYN "���Ի�Ӳ�����ļ�ס��$P" CYN "��һ�У�\n"NOR;
        }
	message_combatd(msg, me, target);

	return 1;
}
