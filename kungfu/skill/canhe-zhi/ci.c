// ci.c �κ�һָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("���κ�һָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("�㲻�������������ʹ�òκ�ָ�أ�\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 100)
                return notify_fail("��Ĳκ�ָ��Ϊ���ޣ�����ʹ�á��κ�һָ����\n");

        if (me->query("neili") < 100)
                return notify_fail("��������������޷����á��κ�һָ����\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û�м����κ�ָ, ����ʹ�á��κ�һָ����\n");

	if( me->query_skill_prepared("finger") != "canhe-zhi" )
		return notify_fail("�������Ĳ��ǲκ�ָ������ʩչ�κ�ָ����\n");

        msg = HIW "$N" HIW "ʳָ�����ʩչ���κ�ָ�ľ�����ʽ��һ������Ϯ��$n"
              HIW "����ǰѨλ��\n" NOR;

        ap = me->query_skill("finger");
        if (living(target))
              dp = target->query_skill("parry") / 2;
        else  dp = 0;
        if (random(ap) > dp)
        {
                me->add("neili", -100);
                me->start_busy(2);
                damage = skill / 2 + random(skill);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 35,
                                           HIR "$n" HIR "��ܲ�������ʱ���öپ�����"
                                           "������һʹ�����ﲻ��һ��\n" NOR);
        } else
        {
                me->add("neili",-40);
                msg += CYN "����$n" CYN "������$N" CYN "����·��������Ų������ʹ$N"
                       CYN "�Ĺ���û�������á�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
