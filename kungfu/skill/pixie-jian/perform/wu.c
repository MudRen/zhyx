// wu.c Ⱥħ����

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        object weapon;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/pixie-jian/wu"))
                return notify_fail("�㻹����ʹ�á�Ⱥħ���衹��\n");

        if (me->query("gender") != "����" && !me->query("tianmo_jieti"))
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

        if (! target || ! me->is_fighting(target))
                return notify_fail("Ⱥħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��û��װ��������������һ�С�\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("�㲢û��ʹ�ñ�а�������޷�ʹ�ô˾��У�\n"); 

        if ((int)me->query("neili") < 300)
                return notify_fail("��������������޷�ʩչȺħ���裡\n");

        if ((lvl = (int)me->query_skill("pixie-jian", 1)) < 350)
                return notify_fail("��ı�а������򲻹����޷�ʩչȺħ���裡\n");

        msg = HIR "$N" HIR "һ�����������α������ޱȣ�������$n"
              HIR "�������У�\n" NOR;
        i = 7;
        if (lvl / 2 + random(lvl) > (int)target->query_skill("parry") || !living(target))
        {
                msg += HIR "$n" HIR "ֻ������ǰһ�����������ܶ���$N"
                       HIR "����Ӱ�����ɰ������⣬�������ˡ�\n" NOR;
                count = (lvl + (int)me->query_skill("riyue-guanghua", 1)) / 2;
                if( me->query_skill_mapped("force") != "riyue-guanghua")
                count /= 2;
                me->add_temp("apply/attack", count);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "���ÿ죬����"
                       "�ҵ�������æ������С��Ӧ�ԡ�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        me->add("neili", -i * 20);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 7 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(6));
        return 1;
}

