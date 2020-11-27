#include <ansi.h>
#include <combat.h>

#define YONG "��" HIY "��ӿ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if (userp(me) && ! me->query("can_perform/bizhen-qingzhang/yong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(YONG "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("bizhen-qingzhang", 1) < 250)
                return notify_fail("��������ƻ�򲻹�������ʩչ" YONG "��\n");

        if (me->query_skill_mapped("strike") != "bizhen-qingzhang")
                return notify_fail("��û�м����������ƣ�����ʩչ" YONG "��\n");

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang")
                return notify_fail("��û��׼���������ƣ�����ʩչ" YONG "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" YONG "��\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ����������ʩչ" YONG "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�����ڵ��������㣬����ʩչ" YONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "���һ����˫�ƻ����һ����Ȧ��˫�Ʒ�����"
		"��ӿ���ȵľ����粨��һ��ӿ��$n��\n" NOR;  

        ap = me->query_skill("strike") + me->query("str") * 10;
        dp = target->query_skill("parry") + target->query("dex") * 8;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "���$N" HIR "����ӿ���ȵĹ�"
                       "�ƣ���ȫ�޷��ֵ����м�ɢ�ң������˺�\n" NOR;
                count = ap / 7;
        } else
        {
                msg += HIC "$n" HIC "�ĵ�΢΢һ������֪�����æ"
                       "�������񣬽߾����ܻ���$N" HIC "����������\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        me->add_temp("apply/attack", count);
        me->add_temp("apply/unarmed_damage", count / 2);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add("neili", -600);
        me->start_busy(1 + random(6));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 2);
        return 1;
}

