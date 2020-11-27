// ji.c ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i, ap, dp;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/ningxue-shenzhao/ji"))
                return notify_fail("�㻹����ʹ����һ�У�\n");

        if (! me->is_fighting(target))
                return notify_fail("�����硹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("unarmed") != "ningxue-shenzhao")
                return notify_fail("��û��׼��ʹ����Ѫ��צ���޷�ʩչ�����硹��\n");

        skill = me->query_skill("ningxue-shenzhao", 1);

        if (skill < 250)
                return notify_fail("�����Ѫ��צ��Ϊ���ޣ��޷�ʹ�á����硹��\n");

        if (me->query_skill("claw",1) < 350)
                return notify_fail("��Ļ���צ����Ϊ���ޣ��޷�ʹ�á����硹��\n");

        if (me->query_skill("force") < 350)
                return notify_fail("����ڹ���򲻹�������ʩչ�����硹��\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת�����γɡ����硹��\n");

        if ((int)me->query("str") < 45)
                return notify_fail("��ı����������޷�ʩչ�����硹��\n");

        if (me->query("neili") < 1000)
                return notify_fail("������������������޷�ʩչ�����硹��\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ�����硹��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һ����Х������Ծ��˫צ�ó�����צӰ�����ƻֺ룬���缲��һ������$n" HIR "����ҪѨ��\n" NOR;

        message_sort(msg, me, target);
        me->add("neili", -50);
        ap = me->query_skill("ningxue-shenzhao, 1") + me->query_skill("drawing, 1") / 3;
        dp = target->query_skill("dodge", 1) + target->query_skill("drawing, 1") / 3;
       
        if (ap / 3 + random(ap) > dp)
                  count = ap / 8;
  
        else count = 0;

        me->add_temp("apply/attack", count);
        me->add_temp("apply/unarmed_damage", count / 3);

        for (i = 0; i < 15; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, i * 2);
        }
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 3);
        me->start_busy(1 + random(5));
        return 1;
}


