// jueming.c ����

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

        if (userp(me) && ! me->query("can_perform/shiying-shenzhao/jueming"))
                return notify_fail("�㻹����ʹ�á���������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�ܿ���ʹ�á���������\n");

        ap = me->query_skill("shiying-shenzhao", 1);

        if (ap < 150)
                return notify_fail("���߱ӥ��צ�ȼ�����, �޷�ʹ�á���������\n");

        if (me->query("neili") < 180)
                return notify_fail("��������������޷����á���������\n");

        msg = HIR "$N" HIR "һ�����ȣ��ֱ������ͻ������һ�Σ����ֳ�צ����$n" HIR
              "ǰ��Ѹ��ץ����\n" NOR;

        dp = target->query_skill("parry", 1);
        if (dp < 1)  dp = 1;
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -150);
                damage = ap + (int)me->query_skill("force", 1);
                damage += random(damage / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "���ܲ�����ǰ�ض�ʱ��ץ��"
                                           "����Ѫ�ۣ����������Һ���\n" NOR);
                me->start_busy(2 + random(3));
        } else
        {
                me->add("neili", -50);
                damage = ap / 2 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIM "$n" HIM "����С����У�ƴ����⣬"
                                           "��˫���Ա�ץ���˼���Ѫӡ��\n" NOR);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

