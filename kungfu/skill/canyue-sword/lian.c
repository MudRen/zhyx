//lian.c ��������
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int)(me->query_skill("sword"));
        j = skill/4;
        i = 5 + (int)me->query("tianmo_jieti/times");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("���������¡�ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query("gender") != "����")
                return notify_fail("�㲻����������,�޷�ʹ����˾�����\n");

        if (!objectp(weapon = me->query_temp("weapon")) )
                return notify_fail("�����ʹ����������ʹ�á��������¡���\n");

        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("��û���ý����޷�ʹ�á��������¡���\n");

        if(me->query_skill_mapped("sword") != "canyue-sword") 
                return notify_fail("��û���ò��½������޷�ʹ�á��������¡���\n");

        if( (int)me->query_skill("canyue-sword", 1) < 220 )
                return notify_fail("��Ĳ��½�����������죬ʹ�������������¡�������\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("����ڹ��ȼ���������ʹ�������������¡�������\n");

        if( (int)me->query("max_neili") < (me->query_skill("force") + i*j + 2000) )
                return notify_fail("���������Ϊ��Ҫ��һ����ߣ�����ʹ�����������¡����ֳ�ǿ���С�\n");

        if( (int)me->query("neili") < (me->query_skill("force") + i*j) )
                return notify_fail("����������̫��������ʹ�á��������¡���\n");


        msg = HIM "\n$N" HIM "��ȻһЦ������"+ weapon->name() + HIM "���һ�����������£���Χ����ǹ������˸��ٲȻһ�����������¡���������\n"
              HIM "��Ȼ����ͼ��ã���ǧ�ǹ⻤��һ�����ʻ������¹���" HIM "$n" HIM "���ϵ����ȥ��\n" NOR;

        message_combatd(msg, me, target);

        me->add_temp("apply/str", 7);
        me->add_temp("apply/damage", j);
        me->add_temp("apply/attack", j);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                msg = HIB "\n�ǹ���ǧ�����¶��𣡣�\n" NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
                me->add("neili", -j);
        }

        me->start_busy(4);

        target->start_busy(1);

        me->add_temp("apply/str", -7);
        me->add_temp("apply/damage", -j);
        me->add_temp("apply/attack", -j);

        return 1;
}

