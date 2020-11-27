#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/qianzhu-wandushou/wan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! me->is_fighting(target))
                return notify_fail("��������졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("��û��׼��ʹ��ǧ�����֣��޷�ʩչ������졣\n");

        skill = me->query_skill("qianzhu-wandushou", 1);

        if (skill < 220)
                return notify_fail("���ǧ��������Ϊ���ޣ��޷�ʩչ������졣\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ������졣\n");

        if (me->query("max_neili") < 3500)
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת����ʩչ������졣\n");

        if (me->query("neili") < 500)
                return notify_fail("������������������޷�ʩչ������졣\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ������졣\n");

        msg = HIG "\n$N" HIG "����һ����Х��ǿ���ھ���ȫ��"
              "�����ֳ���������֮ɫ���ȵ�����"RED"�������"HIG"��,˫"
              "����\nȻ�ĳ�����ʱ�ó��������ɫ��Ӱ��������"
              "��������$n" HIG "ȫ��\n" NOR;

        message_combatd(msg, me, target);

        me->add("neili", -300);        
        count = (me->query_skill("hand") + me->query_skill("force"))/10 + me->query_skill("wudu-qishu", 1)/5;
        count = (int) count;		
        me->add_temp("apply/attack", count);
        me->add_temp("apply/unarmed_damage", count / 2);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count/2);
        me->start_busy(1 + random(5));

        return 1;
}
