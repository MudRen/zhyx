// jie.c �������ӡPFM��������
// update by xiner 20090218

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("����١�ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����١�ֻ�ܿ���ʹ�á�\n");
                
        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ���������޷�ʩչ��١�\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������\n");

        if ((int)me->query("qi") < 1000)
                return notify_fail("����������ڲ�����\n");

        if ((int)me->query_skill("jiuzi-zhenyan", 1) < 250)
                return notify_fail("��ľ������Ի�򲻹����޷�ʹ����٣�\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ����٣�\n");

        if (me->query_skill_prepared("hand") != "jiuzi-zhenyan")
              return notify_fail("������û��׼��ʹ�þ������ԣ��޷�ʹ����٣�\n");

        msg = HIW "$N" HIW "һ�����ȣ�˫����Ȼ������"
              "ɲ�Ǽ�ֻ����������ӡ����ǵط�ӵ������"
              "���ƻֺ룬�����ױȡ�\n" NOR;

        ap = me->query_skill("hand") + me->query_skill("buddhism") + me->query_skill("lamaism");

        dp = target->query_skill("parry") + target->query_skill("buddhism") + target->query_skill("lamaism");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                count = ap / 8;
                msg += HIR "$n" HIR "���$P" HIR "����ɽ�������ƣ���ȫ"
                       "�޷��ֵ���Ψ���˺�\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����Ӧս���߾����ܻ���$P" HIC
                       "�⼸�ơ�\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -500);
        me->add("qi", -200);    
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));
        me->add_temp("apply/attack", -count);

        return 1;
}