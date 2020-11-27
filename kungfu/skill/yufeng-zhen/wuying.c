// wuying.c

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
                return notify_fail("��Ӱ��ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            (string)weapon->query("skill_type") != "throwing")
                return notify_fail("���������в�û����������룬��ôʩչ��Ӱ�룿\n");

        if (weapon->query_amount() < 5)
                return notify_fail("����Ҫ���������������ʩչ��Ӱ�롣\n");

        if ((skill = me->query_skill("yufeng-zhen", 1)) < 100)
                return notify_fail("���������ַ�������죬����ʹ����Ӱ�롣\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�����������ˡ�\n");

        me->add("neili", -80);
        weapon->add_amount(-5);

        msg= HIY "$N" HIY "���ţ��㲻�ƣ�����ֻ������һ����ֻ��"
             "���㺮��һ����������Ϯ��$n" HIY "��\n" NOR;

        me->start_busy(2);
        my_exp = me->query("combat_exp") + skill * skill / 10 * skill;
        ob_exp = target->query("combat_exp");
        if (random(my_exp) > ob_exp || !living(target))
        {
                msg += HIR "���$p" HIR "��Ӧ����������$P" + HIR "һ" +
                       weapon->query("base_unit") + weapon->name() +
                       HIR "��\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 3), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me, target,
                               me->query("jiali") + 120);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += HIG "����$p" HIG "���ݲ��ȣ����ɵ�������$P" HIG "������" +
                       weapon->name() + HIG "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}
