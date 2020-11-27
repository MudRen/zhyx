#include <ansi.h>
#include <combat.h>

#define LUAN "��" HIM "��Ħ������" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/damo-jian/luan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" LUAN "��\n");

        if ((int)me->query_skill("damo-jian", 1) < 250)
                return notify_fail("���Ħ����������죬����ʩչ" LUAN "��\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("��û�м�����Ħ����������ʩչ" LUAN "��\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("���������Ϊ����������ʩչ" LUAN "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�����ڵ��������㣬����ʩչ" LUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "$N" HIM "��ת���棬����" + weapon->name() +
              HIM "�Ϲ⵴�����������������ν�������$n"
              HIM "ȫ����\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force");
        dp = target->query_skill("force") * 2;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           (: final, me, target, damage :));
                me->start_busy(3);
                me->add("neili", -300);
        } else
        {
                msg += CYN "����$n" CYN "�������ʹ��$P"
                       CYN "��һ��û�����κ����á�\n" NOR;
                me->start_busy(4);
                me->add("neili", -100);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("damo-jian", 1);

        target->affect_by("damo_luanqi",
                ([ "level"    : lvl + random(lvl),
                   "id"       : me->query("id"),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "��ʱ$n" HIR "��ͷһ���Ի����ڵ�������ʱ"
                "����ʹ�����Ĵ����ߡ�\n" NOR;
}
