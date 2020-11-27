// �������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object du;
        int damage;
        int ap, dpa, dpb;
        string msg;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ��ֵ�����档\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 80)
                return notify_fail("��ĳ����ƻ�򲻹���\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�ó����ơ�\n");

        if (!(me->query_skill_mapped("strike") == "chousui-zhang"))
                return notify_fail("�㲢û�м��������ƣ�����û��棿\n");

        if (!(me->query_skill_prepared("strike") == "chousui-zhang"))
                return notify_fail("�㲢û��׼�������ƣ�����û��棿\n");


        if ((int)me->query_skill("poison", 1) < 80)
                return notify_fail("��Ļ���������򲻹���\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 80)
                return notify_fail("��Ļ����󷨻�򲻹���\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("���������Ϊ���㣬�޷���������������档\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("��������Ϣ���㣬�޷���������������档\n");

        if (! objectp(du = me->query_temp("handing")))
                return notify_fail("������Ҫ����(hand)һЩ��ҩ��Ϊ���ӡ�\n");

        if (! mapp(du->query("poison")))
                return notify_fail(du->name() + "�ֲ��Ƕ�ҩ���޷����䣿\n");

        msg = HIR "$N" HIR "�����һЦ������������������ָ��׼$n"
              HIR "����һ����ֻ��һ�����ɫ�Ļ�����$n" HIR "Ʈȥ��\n\n" NOR;
        me->start_busy(2 + random(2));
        me->add("neili", -200);
        lvl = me->query_skill("chousui-zhang", 1);

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
                        msg += CYN "$n" CYN "���Ʋ����æ��Ų���Σ��ܿ���$N�Ĺ�����\n" NOR;
                        target->start_busy(1);
                } else
                {
                        msg += HIG "$n" HIG "ֻ�����˿�һ�����ˣ��漴�������ľ������\n" NOR;
                        target->affect_by("fire_poison",
                                       ([ "level" : me->query("jiali") + random(me->query("jiali")),
                                          "id"    : me->query("id"),
                                          "duration" : lvl / 50 + random(lvl / 20) ]));
                        target->start_busy(1);
                }
        }

        destruct(du);
        message_combatd(msg, me, target);

        return 1;
}

