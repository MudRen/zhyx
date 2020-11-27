// �������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object du;
        int damage;
        int ap, dpa, dpb;
        string msg,str;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ��ֵ������\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 120)
                return notify_fail("��ĳ����ƻ�򲻹���\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�ó����ơ�\n");

        if (!(me->query_skill_mapped("strike") == "chousui-zhang"))
                return notify_fail("�㲢û�м��������ƣ�����û���\n");

        if (!(me->query_skill_prepared("strike") == "chousui-zhang"))
                return notify_fail("�㲢û��׼�������ƣ�����û���\n");


        if ((int)me->query_skill("poison", 1) < 120)
                return notify_fail("��Ļ���������򲻹���\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 120)
                return notify_fail("��Ļ����󷨻�򲻹���\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("���������Ϊ���㣬�޷��������������\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������Ϣ���㣬�޷��������������\n");

        if (! objectp(du = me->query_temp("handing")))
                return notify_fail("������Ҫ����(hand)һЩ��ҩ��Ϊ���ӡ�\n");

        if (! mapp(du->query("poison")))
                return notify_fail(du->name() + "�ֲ��Ƕ�ҩ���޷����䣿\n");

        msg = HIR "$N" HIR "����������һ�����ȣ���׼$n"
              HIR "�͵ص���һ�����ɫ�Ļ���Я��һ��������$p" HIR "��ȥ��\n\n" NOR;
        me->start_busy(2 + random(2));
        me->add("neili", -350);

        lvl = me->query_skill("chousui-zhang", 1);
        damage = lvl + random(lvl*3);

        if (living(target))
                dpa = target->query("max_neili") * 5 / 4;
        else    dpa = 0;

        if (me->query("max_neili") / 2 + random(me->query("max_neili")) < dpa)
        {
                msg += WHT "����$n" WHT "��Ȼ�����������������һ�����㽫����Ϩ��\n" NOR;
        } else
        {
                ap = me->query_skill("poison", 1) / 2 +
                     me->query_skill("force");
                if (living(target))
                        dpb = target->query_skill("dodge") * 3 / 2;
                else    dpb = 0;
                if (ap / 2 + random(ap) < dpb)
                {
                        msg += CYN "$n" CYN "���Ʋ����æ��Ų���Σ��ܿ���$N" CYN "�Ĺ�����\n" NOR;
                        target->start_busy(1);
                } else
                {
                        msg += HIR "���ֻ��$n" HIR "һ���Һ����ѱ�������У�Ƥ���յá����͡����졣\n" NOR;
                        target->affect_by("fire_poison",
                                       ([ "level" : me->query("jiali") * 3 / 2 + random(me->query("jiali") * 3 / 2),
                                          "id"    : me->query("id"),
                                          "duration" : lvl / 30 + random(lvl / 15) ]));
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/2, me);
                        target->receive_damage("jing", damage / 2, me);
                        target->receive_wound("jing", damage/4, me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        msg += "($n"+str+")\n";
                        target->start_busy(1);
                }
        }

        destruct(du);
        message_combatd(msg, me, target);

        return 1;
}

