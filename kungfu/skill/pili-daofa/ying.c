// ying.c ������������Ӱ���ء�
// By Haiyan

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, zhao;

        if (! target) target = offensive_target(me);


        if (! target || ! me->is_fighting(target))
                 return notify_fail("����Ӱ���ء�ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "blade")
                 return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("pili-daofa", 1) < 120)
                 return notify_fail("�������������򲻹����޷�ʩչ����Ӱ���ء���\n");

        if (me->query("neili") < 120)
                return notify_fail("�����������������ʹ�á���Ӱ���ء���\n");

        msg = HIC "$N" HIC "�����䣬����" + weapon->name() + "����ƬƬ��Ӱ����$n" + HIC
              "һ����ȥ��\n" NOR; 

        ap = me->query_skill("blade", 1) / 2 + me->query_skill("pili-daofa", 1);
        dp = target->query_skill("dodge") / 2 + target->query_skill("parry", 1);

        if ( ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "ֻ��$p" HIR "һ���ҽУ�"
                      "���϶�ʱ������Ѫ��ģ������Ѫ������\n" NOR;
                zhao = 5;
                count = ap / 5;
        } else
        {
                msg += CYN "����$p" CYN "�����񵲣���$P" CYN
                       "�Ĺ������⡣\n" NOR;
                zhao = 0; 
                count = 0;
        }
                
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", count);
        for (i = 0; i < zhao; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(3);

        return 1;
}

