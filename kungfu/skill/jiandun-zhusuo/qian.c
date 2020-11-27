#include <ansi.h>
#include <combat.h>

#define QIAN "��" HIW "ǧͷ����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/jiandun-zhusuo/qian"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" QIAN "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" QIAN "��\n");

        if (me->query_skill("jiandun-zhusuo", 1) < 180)
                return notify_fail("��Ľ���������Ϊ����������ʩչ" QIAN "��\n");

        if (me->query("neili") < 400)
                return notify_fail("�����������������ʩչ" QIAN "��\n");

        if (me->query_skill_mapped("whip") != "jiandun-zhusuo")
                return notify_fail("��û�м�����������������ʩչ" QIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        if (me->query_skill("zhanshen-xinjing", 1) < 180)
                return notify_fail("���ս���ľ���Ϊ����������ʩչ" QIAN "��\n");

		  if (me->query_skill_mapped("force") != "zhanshen-xinjing")
                return notify_fail("��û�м���ս���ľ�������ʩչ" QIAN "��\n");
        wname = weapon->name();

       // damage = me->query_skill("jiandun-zhusuo", 1)+(int)me->query_skill("zhanshen-xinjing",1)/4;
       // damage += random(damage*2);

        ap = me->query_skill("whip")+random((int)me->query_skill("zhanshen-xinjing",1)/2);
        dp = target->query_skill("parry");

        msg = HIG "$N" "һ����ߣ�����"HIR"ս���ľ�"HIG"�������⶯������������\nֻ��ǧǧ�������Ӱ��������,"  +
               "һ�С�ǧͷ��������׼$n�ҵ�������\n\n" NOR;
        if (ap *3/ 4 + random(ap) > dp)
        {    damage = ap+random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "������ˣ�ȴ��Ȼ��������"
                                           "$P" HIR "���е���ҪѨ����ʱ������Ѫ��\n"
                                           NOR);
        } else
        {
                msg += CYN "$p" CYN "���������Ӳ������$P"
                       CYN "��һ�޼ܿ���˿������\n" NOR;
        }

        ap = me->query_skill("whip")+random((int)me->query_skill("zhanshen-xinjing",1)/3);
        dp = target->query_skill("dodge");

        msg += "\n" HIW "ȴ��$N" HIW "�粽��ǰ������" + wname +
               HIW "����һ�䣬��ת���ʣ�����$n" HIW "��ȥ��\n" NOR;
        if (ap *2/ 3 + random(ap) > dp)
        {damage = ap+random(ap*2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "����$p" HIR "΢΢һ��䣬�ѱ�$P"
                                           HIR "���г��У���Ѫ�Ĵ��ɽ���\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "��æ����һ��������"
                       "��Ծ�𣬶㿪����һ�С�\n" NOR;
        }

        ap = me->query_skill("whip")+random((int)me->query_skill("zhanshen-xinjing",1)/4);
        dp = target->query_skill("force");

        msg += "\n" HIW "�������ּ�$N" HIW "������𣬵��ֽ�" + wname +
               HIW "�����趯����ճ���$n" HIW "Ȧȥ��\n" NOR;
        if (ap *3/5 + random(ap) > dp)
        {damage = ap+random(ap*3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "��ʱ������ž����һ�����죬$n" HIR
                                           "����" + wname + HIR "������գ�����"
                                           "ˤ�£���Ҳ��������\n" NOR);
        } else
        {
                msg += CYN "��$p" CYN "һ������������ʱ����"
                       "�����⣬�㽫��ʽ���������Ρ�\n" NOR;
        }
        me->start_busy(3 + random(4));
        me->add("neili", -500);
        message_combatd(msg, me, target);
        return 1;
}
