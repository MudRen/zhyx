// puji.c ����˻�
// wrote by kasumi 2007.7
#include <ansi.h>

inherit F_SSERVER;

#define PUJI "��" HIG "����˻�" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
       // if (userp(me) && ! me->query("can_perform/hamagong/puji"))
         //       return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(PUJI "ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(PUJI "ֻ�ܿ���ʹ�á�\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("hamagong", 1) < 200)
                return notify_fail("��ĸ�󡹦��򲻹����޷�ʩչ" PUJI "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�������޷�ʩչ" PUJI "��\n");

        if (me->query_skill_prepared("unarmed") != "hamagong")
                return notify_fail("������û��׼��ʹ�ø�󡹦���޷�ʩչ" PUJI "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = MAG "$N˫��һ�䣬�������������󡱵�һ����У������󡹦������˫���뷢��\n"
              MAG "������ɽ�麣Х��Ϯ��$n��\n" NOR;      
        

        ap = me->query_skill("unarmed");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 4;
                msg += HIY "$n" HIY "��$P" HIY "��һ���������ͣ�������"
                       "�������ɴ��һ��������������������\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����С��$P" HIC
                       "�����У���Ų������С���мܡ�\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -300);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2)==0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(4));
        me->add_temp("apply/attack", -count);

        return 1;
}

