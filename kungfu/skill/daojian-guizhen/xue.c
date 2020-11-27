#include <ansi.h>
#include <combat.h>

#define XUE "��" HIW "������" HIR "Ѫ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon, weapon2;
        int i, count, damage;
        int ap, dp;

        if (me->query_skill("daojian-guizhen", 1) < 200)
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(XUE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword"
           && (string)weapon->query("skill_type") != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" XUE "��\n");

        type = weapon->query("skill_type");

        if (me->query_skill(type, 1) < 250)
                return notify_fail("���" + to_chinese(type) + "̫�"
                                   "����ʩչ" XUE "��\n");

        if (me->query_skill_mapped(type) != "daojian-guizhen")
                return notify_fail("��û�м����������棬����ʩչ" XUE "��\n");

        if (me->query_skill("daojian-guizhen", 1) < 250)
                return notify_fail("��Ľ�����ȼ�����������ʩչ" XUE "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�����ڵ���������������ʩչ" XUE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����" + weapon->name() + HIW "���һ��"
              "������" NOR + WHT "���ҵ���" HIW "������" NOR + WHT
              "��ҽ���" HIW "������ʩ������ʱ��\n���㣬����ҹ��"
              "���գ�����ǵ�����$n" HIW "������һ�С�" HIW "����"
              "��" HIR "Ѫ" HIW "����\n" NOR;

        ap = me->query_skill("daojian-guizhen", 1) * 3 / 2 +
             me->query_skill("martial-cognize", 1);

        dp = target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$n" HIW "ֻ���������⽣Ӱ���Լ���"
                       "�����ٸ��ۻ����ң��ĵ׺�����Ȼ������\n" NOR;
                count = ap / 6;
                me->set_temp("daojian-guizhen/max_pfm", 1);
        } else
        {
                msg += HIG "$n" HIG "ͻȻ�����Լ����ܽԱ�����"
                       "��Ӱ����Χ����֪�����æС���мܡ�\n" NOR;
                count = ap / 12;
        }
        message_combatd(msg, me, target);

        me->add("neili", -300);
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count * 2 / 3);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count * 2 / 3);
        me->delete_temp("daojian-guizhen/max_pfm");
        me->start_busy(1 + random(5));
        return 1;
}