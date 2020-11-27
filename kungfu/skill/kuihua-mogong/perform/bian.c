#include <ansi.h>
#include <combat.h>

#define BIAN "��" HIG "�ޱ��޼�" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", }); 

int perform(object me, object target)
{
        int damage;
        string msg, name;
        object weapon;
        int lvl, ap, dp;

        if (userp(me) && ! me->query("can_perform/pixie-jian/po"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin")
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ" BIAN "��\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ" BIAN "��\n");
        }

        if ((int)me->query_skill("kuihua-mogong", 1) < 260)
                return notify_fail("��Ŀ���ħ��������죬����ʩչ" BIAN "��\n");

        if ((int)me->query("max_neili") < 3700)
                return notify_fail("���������Ϊ���㣬����ʩչ" BIAN "��\n");

        if (me->query("neili") < 300)
                return notify_fail("�����ڵ��������㣬����ʩչ" BIAN "��\n");

        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" BIAN "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" BIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if (target->query_temp("no_perform"))
                return notify_fail("�Է������Ѿ��޷������������ŵ������ɡ�\n");

        if (me->query_temp("weapon"))
                name = "����" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIR "$N" HIR "һ����Х��������Ȼ��ת������" + name +
              HIR "��ʱ������������������ǧ������룬�������$n" HIR "��\n" NOR;

        ap = me->query_skill("kuihua-mogong", 1) +
             me->query_skill("dodge");

        dp = target->query_skill("martial-cognize", 1) +
             target->query_skill("dodge");

        if (ap * 11 / 20 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                me->add("neili", -200);
        } else
        {
                msg += CYN "$n" CYN "��֮��ȫȻ�޷��мܣ���æ"
                       "�����������ߣ��㿪����һ�С�\n" NOR;
                me->start_busy(3);
                me->add("neili", -150);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        target->set_temp("no_perform", 1);
        call_out("bian_end", 10 + random(ap / 50), me, target);
        return HIR "$n" HIR "ֻ����ǰ���������������漴ȫ��һ��"
               "��ʹ������Ѫ�������������\n$p��Ȼ��һ��������"
               "�����������������ƻ�ɢһ�㣬ȫȻ�޷����ơ�\n" NOR;
}

void bian_end(object me, object target)
{
        if (target && target->query_temp("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
                target->delete_temp("no_perform");
	}
	return;
}