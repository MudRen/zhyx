// ʥ�����

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
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʩչʥ�������\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ��ʥ��ȭ��\n");

        if (!(me->query_skill_mapped("cuff") == "shenghuo-quan"))
                return notify_fail("�㲢û�м���ʥ��ȭ�������ʥ�������\n");

        if (!(me->query_skill_prepared("cuff") == "shenghuo-quan"))
                return notify_fail("�㲢û��׼��ʥ��ȭ�������ʥ�������\n");

        if ((int)me->query_skill("shenghuo-quan", 1) < 60)
                return notify_fail("���ʥ��ȭ��򲻹���\n");

        if ((int)me->query("max_neili") < 200)
                return notify_fail("���������Ϊ���㣬�޷�������ʩչʥ�������\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("��������Ϣ���㣬�޷�������ʩչʥ�������\n");

        msg = HIR "ֻ��$N" HIR "һ����Х������ͻ��һƬ��⣬˫ȭ�����ؿڣ���̴Ӽ��ȭͷ����Ϊ��ɫ��\n\n"
              "$N" HIR "����һ������˫ȭ�����ɳ����������˳�$n" HIR "�ɾ��ȥ�����˸е�һ����Ϣ��\n\n"NOR;

        me->start_busy(1 + random(2));
        me->add("neili", -50);

        lvl = me->query_skill("shenghuo-quan", 1);
        damage = lvl + random(lvl/2);

        ap = me->query_skill("cuff");
        ap += me->query_skill("force");
        ap += me->query_str() * 10;
        ap += random(ap/2);
        dp = target->query_skill("dodge");
        dp += target->query_skill("force");
        dp += target->query_dex() * 10;
        dp += random(dp/2);
        if (ap > dp || !living(target))
        {
                msg += HIR "$n" HIR "������ȭ������ӿ����ֻ������һ���ʹ��"
                               "�ѱ��������ҵ�ȭ�����һ�ϯ��ȫ�������ƺ�һ����\n\n" NOR;
                        target->receive_damage("qi", damage, me );
                        target->receive_wound("qi", random(damage/2), me);
                        target->start_busy(2);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        msg += "($n"+str+")\n";
        } else
        {
                msg += HIY "$n" HIY "��״��æ����������˫����"
                       "�����μ��ˣ��ܿ���$N" HIY "�������������ȭ�硣\n\n";
        }

        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}

