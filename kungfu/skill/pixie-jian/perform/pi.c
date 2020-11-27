// pi.c Ⱥа����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("��Ⱥа���ס�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query("gender") != "����" && !me->query("tianmo_jieti"))
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 120)
                return notify_fail("��ı�а������Ϊ���ޣ����ڲ���ʹ�á�Ⱥа���ס���\n");

        if (me->query("neili") < 100)
                return notify_fail("��������������޷����á�Ⱥа���ס���\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ֻ��װ��������ʩչ��Ⱥа���ס���\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("�㲢û��ʹ�ñ�а�������޷�ʹ�ô˾��У�\n"); 

        if (weapon)
        {
                msg = HIR "$N" HIR "���κ�Ȼ��죬��ĳ���$n"
                      HIR "�����е�" + weapon->name() + HIR "ָָ��㣬��ͬ"
                      HIR "��ҹ����һ�㣬����â����$p" HIR "��\n" NOR;
        } else
        {
                msg = HIR "$N" HIR "��Ȼ����$n" HIR "�������"
                      HIR "����˼�飬�������ȣ����־�����������$n" HIR "��\n" NOR;
        }

        message_combatd(msg, me, target);
        count = skill + (int)me->query_skill("riyue-guanghua", 1);
        count /= 2;

        if( me->query_skill_mapped("force") != "riyue-guanghua")
        count /= 2;

        me->add_temp("apply/attack", count);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(3));
        me->add_temp("apply/attack", -count);

        return 1;
}

