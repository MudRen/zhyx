//lian.c ��ϼ����
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int)(me->query_skill("cuff"));
        j = skill/4;
        i = 5 + (int)me->query("tianmo_jieti/times");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("����ϼ���졹ֻ����ս���жԶ���ʹ�á�\n");

        if(me->query_skill_mapped("cuff") != "luorishenquan-cuff") 
                return notify_fail("��û����������ȭ���޷�ʹ�á���ϼ���졹���У�\n");

        if (me->query_skill_prepared("cuff") != "luorishenquan-cuff")
                return notify_fail("��û��׼��ʹ��������ȭ���޷�ʩչ����ϼ���졹���С�\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ��ȭ�����С�\n");

        if( (int)me->query_skill("luorishenquan-cuff", 1) < 220 )
                return notify_fail("���������ȭ����������죬ʹ��������ϼ���졹������\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("����ڹ��ȼ���������ʹ��������ϼ���졹������\n");

        if( (int)me->query("max_neili") < (me->query_skill("force") + i*j + 2000) )
                return notify_fail("���������Ϊ��Ҫ��һ����ߣ�����ʹ������ϼ���졹���ֳ�ǿ���С�\n");

        if( (int)me->query("neili") < (me->query_skill("force") + i*j) )
                return notify_fail("����������̫��������ʹ�á���ϼ���졹��\n");


        msg = HIM "\n$N" HIM "����Ʈ�ɣ�˫ȭ�������������ȫ�Ƿ����ȭӰ����Ȼ���ǡ���ϼ���졻��\n" NOR;

        message_combatd(msg, me, target);

        me->add_temp("apply/str", 7);
        me->add_temp("apply/damage", j);
        me->add_temp("apply/attack", j);

        while (i-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(4);

        target->start_busy(1);

        me->add_temp("apply/str", -7);
        me->add_temp("apply/damage", -j);
        me->add_temp("apply/attack", -j);

        return 1;
}

