// tan.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ָֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            (string)weapon->query("skill_type") != "throwing" ||
            weapon->query_amount() < 1)
                return notify_fail("���������в�û�����Ű�������ôʩչ��ָ��\n");

        if ((skill = me->query_skill("tanzhi-shentong", 1)) < 100)
                return notify_fail("��ĵ�ָ��ͨ������죬����ʹ�õ�ָ��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�����������ˡ�\n");

        me->add("neili", -90);
        weapon->add_amount(-1);

        msg = HIC "$N" HIC "��ָ�ᵯ��ֻ���ƿ���������һ" +
             weapon->query("base_unit") + weapon->name() + HIC "���ٷɳ�" +
             "������$n" HIC "��\n" NOR;

        me->start_busy(2);
        my_exp = me->query("combat_exp") + skill * skill / 10 * skill;
        ob_exp = target->query("combat_exp");
        if (random(my_exp) > ob_exp * 2 / 3 || !living(target))
        {
                msg += HIR + weapon->name() + HIR "���úÿ죬$n"
                       HIR + "һ�����ܲ����������˸����У�����һ"
                       "���ʹ�������˼�����Ҫɢ���ˡ�\n" NOR;
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me, target,
                               me->query("jiali") + 150);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
                target->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "����һ���������$P" HIG "������" +
                       weapon->name() + CYN "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}
