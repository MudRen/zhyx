// wannian.c ������

#include <ansi.h>
#include <combat.h>

#define WANNIAN "��" HIM "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, qi, maxqi;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/sad-strike/wannian")) 
                return notify_fail("�㻹û��ѧ�ᡸ�����ҡ���һ�У�\n");
        if (! target || ! me->is_fighting(target))
                return notify_fail(WANNIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�����ű�����γ���Ȼ�����Ʒ���\n");
        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("����ڹ���򲻹���ʹ����" WANNIAN "��\n");

        if (me->query_skill_mapped("strike") != "sad-strike" &&
            me->query_skill_mapped("unarmed") != "sad-strike" ||
            me->query_skill_prepared("unarmed") != "sad-strike" &&
            me->query_skill_prepared("strike") != "sad-strike")
        return notify_fail("������û��׼��ʹ����Ȼ�����ƣ��޷�ʹ�� " WANNIAN "��\n");

        if ((int)me->query_skill("sad-strike", 1) < 250)
                return notify_fail("�����Ȼ�����Ʋ�������������ʹ��" WANNIAN "��\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("��������������޷�ʹ��" WANNIAN "��\n");

        msg = HIM "$N" HIM "���������ң�û����ɵĻ��������ĳ�һ�ƣ��л��㱣�\n"
              HIM"����ԼԼ���������ޣ�����" HIR "����Ȼ�����ơ�" HIM "����֮���ڣ�����\n" NOR;

        qi = me->query("eff_qi");
        maxqi = me->query("max_qi");

        ap = me->query_skill("force") + me->query_str() * 2;
        dp = target->query_skill("dodge") + target->query_dex() * 2;

	if (qi < (maxqi * 0.4)) ap += ap/3;

        if(ap/2 + random(ap) > dp || !living(target))
	{
		if(qi > (maxqi * 0.4))
	        {
	                me->start_busy(3);
        		damage = ap * 2;
                        me->add("neili",-damage/2);
	                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
        	                HIR "$n" HIR "����ܵù��ˣ����һ�죬�����ؿڣ���Ѫ���磡����\n" NOR);
        	}
	        else 
		{
                	me->start_busy(3);
	                damage = ap * 2 + random(ap*2);
                        me->add("neili",-damage/2);
	        	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
        	                HIC "�˿�������ͷ����ʹ����֮�ʣ�" HIC "$N" HIC "�ġ���Ȼ�����ơ�����������\n" HIR "$n" HIR "���ؿ�����ǧ���ʯײ������ʹ�ޱȣ�����\n" NOR);
        	}
                target->start_busy(1);
	}
	else
        {
                msg += HIG "$n"HIG"ð�����ˣ�$N"HIG"���Ʒ�����ؿ��ӹ���"
                       HIG "$n" HIG "��ʱһ����Ϣ��\n" NOR;
                me->start_busy(2);
        }

        message_combatd(msg, me, target);

        return 1;
}
