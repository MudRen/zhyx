// zhangzhen.c �����л�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHANGZHEN "��" HIW "�����л�" NOR "��"

int perform(object me, object target)
{
	string msg;
        int ap, dp;
        int i, times, count, damage;

        if (userp(me) && ! me->query("can_perform/china-aojue/zhangzhen"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(ZHANGZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("����ֻ�ܿ���ʩչ��\n");

	if ((int)me->query_skill("china-aojue", 1) < 200)
		return notify_fail("����л�����������񣬲���ʹ��" ZHANGZHEN "��\n");	

        if ( me->query_skill_prepared("strike") != "china-aojue")
                return notify_fail("��û��׼��ʹ���л��������޷�ʩչ" ZHANGZHEN "��\n");

	if ( me->query("neili") < 500 )
		return notify_fail("�����������������ʹ��" ZHANGZHEN "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("china-aojue", 1);
        dp = target->query_skill("parry", 1);


        msg = HIW "$N" HIW "ŭ��һ����˫�ִ󿪴�ϣ�"
              "���޻��ɵ���$n��������һ�ƣ�\n" NOR;

        if (ap * 4 / 5 + random(ap) > dp)
        { 
                damage = ap * 2  + random(ap);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "ֻ��$n" HIR "һ���мܲ��ȣ��ؿ��ѱ�"
                                           "$N˫�����У���ʱŻ��������Ѫ��\n" NOR);
        } else
        {
                me->add("neili", -100);                
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }

         message_sort(msg, me, target);


	
         msg = HIY "������$N" HIY "˫�ƽ������������ƣ�������ɽ��������$n"
              HIY "��ȥ��\n" NOR;
        
        count = ap / 3;

        if (count >100 ) count = 100;

        me->add_temp("apply/attack", count);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, i * 3 );
        }
        me->start_busy(2 + random(3));
        me->add("neili", -300);

        me->add_temp("apply/attack", -count);
	 message_combatd(msg, me, target);

	return 1;
}
