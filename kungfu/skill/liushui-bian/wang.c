// wang.c ������ˮ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/liushui-bian/wang"))
                return notify_fail("�㻹����ʹ�á�������ˮ����һ������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ˮ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        ap = me->query_skill("liushui-bian",1);

        if (ap < 180)
                return notify_fail("�����ˮ�޷��ȼ�����, ����ʹ�á�������ˮ����\n");

        if (me->query("neili") < 200)
                return notify_fail("��������������޷����á�������ˮ����\n");

        msg = HIC "$N" HIC "һ�����е�" + weapon->name() + HIC
              "�����һ��޻����漴�����ڱۣ������᳤���ֱ��$n" HIC
              "������\n" NOR;

        dp = target->query_skill("dodge", 1);
        if (dp < 1)  dp = 1;
        if (ap / 2 + random(ap) > dp || ! living(target))
        {
                me->add("neili", -150);
                damage = ap + (int)me->query_skill("force", 1);
                damage = damage / 2 + random(damage / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "$n" HIR "���������ͣ�������������ʱ����"
                                           "�����У�����һ�����������ʹ��\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                me->add("neili", -40);
                msg += CYN "����$n" CYN "�������ƣ�����ܹ�$N"
                       CYN "��һ�С�\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

