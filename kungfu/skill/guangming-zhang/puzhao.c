// ʥ������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        int ap,dp;
        string msg,str;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʩչʥ�����ա�\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�ù������ơ�\n");

        if (!(me->query_skill_mapped("strike") == "guangming-zhang"))
                return notify_fail("�㲢û�м����������ƣ������ʥ�����գ�\n");

        if (!(me->query_skill_prepared("strike") == "guangming-zhang"))
                return notify_fail("�㲢û��׼���������ƣ������ʥ�����գ�\n");

        if ((int)me->query_skill("guangming-zhang", 1) < 80)
                return notify_fail("��Ĺ������ƻ�򲻹���\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("���������Ϊ���㣬�޷�������ʩչʥ�����ա�\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("��������Ϣ���㣬�޷�������ʩչʥ������      ��\n");

        msg = HIR "ֻ��$N" HIR "��ɫ��ׯ����ϲ��ŭ���޴��ޱ��������૲������������ʢ��\n\n"
              "$N" HIR "˫�ƻ���̧������ҫ�۵�Ѫɫ��â���������ƣ�������������ף�\n\n"
              "��Ȼ�䣬$N" HIR "������Х��˫��Ѹ���Ƴ�����ɫ��â���Ź������˽�$n������Χ������\n\n"NOR;

        me->start_busy(1 + random(2));
        me->add("neili", -50);

        lvl = me->query_skill("guangming-zhang", 1);
        damage = lvl + random(lvl/2);
        damage += me->query("jiali");

        ap = me->query_skill("strike");
        ap += me->query_skill("force");
        ap += me->query_str() * 10;
        ap += random(ap/2);
        if (living(target))
        {
                dp = target->query_skill("dodge");
                dp += target->query_skill("force");
                dp += target->query_dex() * 10;
                dp += random(dp/2);
        }  else dp = 0;
        if (ap < dp)
        {
                msg += HIY "$n" HIY "�������񣬲������ۺ�â������"
                       "�����μ�����������$N" HIY "����������Ŀ���һ�ơ�\n\n";
        } else
        {
                msg += HIR "$n" HIR "ֻ������ǰ���һƬ����Ҳ������$N�����Σ�"
                               "��ʧɫ�£������Ѿ�ϯ���ֹ�������ؿڸ�����ӡ��һ�ƣ�������Ѫ���磡\n\n" NOR;
                        target->receive_damage("qi", damage, me );
                        target->receive_wound("qi", random(damage/2), me);
                        target->start_busy(2);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        msg += "($n"+str+")\n";
        }

        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}

