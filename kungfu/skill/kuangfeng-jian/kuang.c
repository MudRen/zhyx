// kuang.c ��罣

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill, q;
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("����硹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("huashan-xinfa", 1) < 120 )
                return notify_fail("��Ļ�ɽ�ķ�������죬����ʹ�á���硹��\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("����罣����ʼʱ��������һ�ѽ���\n");
        if ((int)me->query("max_neili") < 600)
                return notify_fail("����ڹ���Ϊ��������δ��ʹ������硹!\n");
        if ((int)me->query("neili") < 120)
                return notify_fail("��������������޷�ʩչ��罣����\n");
        if ((int)me->query_skill("kuangfeng-jian", 1) < 120)
                return notify_fail("��Ŀ�罣���������ң��޷�ʩչ����硹��\n");
        msg = HIR "$N" HIR "���һ�������е�" + weapon->name() +
              HIR "�����缲��һ��������" HIR "$n"
              HIY "\n\n��һ����̾:  \n" NOR;
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", 200);

        me->add("neili", -100);
        skill = (int) (me->query_skill("kuangfeng-jian",1) / 50);
        q = 5 + skill;
        for (i = 1; i < q; i++)
        {
                if (! me->is_fighting(target))
                        break;
            me->add("neili", -20);
                msg = HIC "-----���ҵ�"+chinese_number(i)+"����\n" NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->start_busy(1 + random(6));
        me->add_temp("apply/attack", -200);

        return 1;
}

