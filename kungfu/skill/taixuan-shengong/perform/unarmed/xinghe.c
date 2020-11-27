// xinghe.c �Ǻ�Ӱ��

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count, n;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("̫���񹦡��Ǻ�Ӱ����ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������ű������޷�ʩչ���Ǻ�Ӱ������\n");
                
        if (me->query_skill_prepared("unarmed") != "taixuan-shengong")
                return notify_fail("������û��׼��ʹ��̫���񹦣��޷�ʹ�á��Ǻ�Ӱ������\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");

        ap = (int)me->query_skill("taixuan-shengong", 1);

        if (ap < 180)
                return notify_fail("���̫���񹦻�򲻹����޷�ʹ�á��Ǻ�Ӱ������\n");

        if ((int)me->query_skill("force", 1) < 300)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ�á��Ǻ�Ӱ������\n");

        n = 5 + ap / 100;

        msg = HIW "$N" HIW "�������˫��һ�㣬��������������Ͼ����"
              "��ʱ����$n" HIW "���ջ���" + chinese_number(n) +
              "�У����к�Х������\n\n" NOR;

        dp = target->query_skill("parry", 1);

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 5;
                msg += HIR "$n" HIR "����ܿ�$P" HIR "����Ӱ����Ĺ��ƣ�"
                       "ȴ�����ѱ�һ�ɾ޴�ľ�����Χ���޴����ܡ�\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����Ӧս����������˫�ۣ���������$P" HIC
                       "�⼸�С�\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);
        me->add("neili", -300);

        for (i = 0; i < n; i++)
        {
                if (! me->is_fighting(target))   break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(3));
        me->add_temp("apply/attack", -count);

        return 1;
}

