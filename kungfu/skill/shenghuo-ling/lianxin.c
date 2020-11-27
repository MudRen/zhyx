#include <ansi.h>
inherit F_SSERVER;
int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

        if (!objectp(weapon = me->query_temp("weapon")))
                return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ����֮�����\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("shenghuo-ling",1);

        if( !(me->is_fighting() ))
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill_mapped("force") != "shenghuo-xuanming")
	    return notify_fail("��ʹ�õ��ڹ�����ʥ����ڤ���޷�ʹ��ʥ�����\n");

        if( skill < 150)
                return notify_fail("���ʥ����ȼ�����, ����ʹ�������\n");

        if( me->query("max_neili") < 1400 )
                return notify_fail("���������Ϊ���㣬�޷����������\n");

        if( me->query("neili") < 600 )
                return notify_fail("��������������޷�ʹ�������\n");

        msg = HIW "$Nһ����ͷ���$n��ǰ����Ȼʹ��ʥ���֮���������" +weapon->name()+ NOR + HIW"�����������ʽ�����ޱȡ�\n" NOR;
        message_combatd(msg, me, target);

        damage = 50 + random(skill);
        ap = me->query_skill("sword")/2 + skill;
        dp = target->query_skill("force");

        if( dp < 1 )
            dp = 1;

        if( random(ap) > random(dp) || !living(target))
        {
                me->add("neili",-200);
                msg = HIR "$nֻ����ǰ���������ͻȻ$N˫�ֳ������Լ���ǰ��ֻ������̫��Ѩһ���ʹ������һ�ڣ�̱���ڵأ�\n" NOR;
                me->start_busy(3);
                target->receive_damage("jing", damage, me);
                target->start_busy(2);
        }
        else
        {
                me->add("neili",-100);
                msg = CYN "$n����ǰ�����������æ����������ǿ�ֵ���������������ò�����������$N������Χ֮�⡣\n"NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}

