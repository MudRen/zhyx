// hua.c ȫ�潣 һ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count,is_yunv=0;

        if (userp(me) && ! me->query("can_perform/quanzhen-jian/hua"))
                return notify_fail("�㻹����ʹ��һ�������塣\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("һ��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 120)
                return notify_fail("���ȫ�潣��������죬����ʹ��һ�������塣\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("�����õĲ������칦���޷�ʩչһ�������壡\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("������칦������죬�޷����һ��������İ��ء�\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("��������������������ʹ��һ�������塣\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("��û�м���ȫ�潣��������ʹ��һ�������塣\n");

        msg = HIC "$N" HIC "վ������������ȫȻ�˵����ϣ�һ�����ȣ�" +
              weapon->name() + HIC "��" HIM "��â" HIC "��ҫ��\n\n" NOR;

	if( me->query_skill("sword") < 200 )
		msg += HIC"$N��Ȼͦ��ǰ�壬"+weapon->query("name")+"ƽָ��ǰ����â���"+HIW+"ѩ������"+HIC+"��һ����Ϊ������Ӱ�������������磡\n\n" NOR;
	else if( me->query_skill("sword") < 300 )
		msg += HIC"$N��Ȼͦ��ǰ�壬"+weapon->query("name")+"ƽָ��ǰ����â���"+HIW+"ѩ������"+HIC+"��һ����Ϊ������Ӱ�������������磡\n\n" NOR;
	else if( me->query_skill("sword") < 400 )
		msg += HIC"$N��Ȼͦ��ǰ�壬"+weapon->query("name")+"ƽָ��ǰ����â���"+HIW+"ѩ������"+HIC+"��һ����Ϊ�塢������Ӱ�������������磡\n\n" NOR;
	else if( me->query_skill("sword") < 500 )
		msg += HIC"$N��Ȼͦ��ǰ�壬"+weapon->query("name")+"ƽָ��ǰ����â���"+HIW+"ѩ������"+HIC+"��һ����Ϊ�ˡ��ŵ���Ӱ�������������磡\n\n" NOR;
	else
		msg += HIC"$N��Ȼͦ��ǰ�壬"+weapon->query("name")+"ƽָ��ǰ����â���"+HIW+"ѩ������"+HIC+"��һ����Ϊ��������Ӱ�������������磡\n\n" NOR;

        ap = me->query_skill("xiantian-gong", 1) + me->query_skill("sword");
        dp = target->query_skill("force");

	//�Է����ʹ�õ��ǹ�Ĺ����Ů��������ǿ����
	//Add by Smallfish
	if (stringp(target->query_skill_mapped("sword")) &&
	    target->query_skill_mapped("sword") == "yunv-jian" &&
            target->query_temp("weapon") &&
            target->query_temp("weapon")->query("skill_type") == "sword")
	{
		dp += target->query_skill("yunv-jian",1);
		is_yunv = 1;
	}

        if (dp < 1) dp = 1;
        if (ap / 3 + random(ap) > dp || !living(target))
        {
                if( !target || !target->is_character() 
                  || !me->is_fighting(target) 
                    || !living (target) ) 
                {
                return -1;
                }
                target->start_busy(1 + random(2));
                me->add("neili", -200);
                if (ap / 4 + random(ap) > dp || !living(target))
                {
                        count = me->query_skill("xiantian-gong", 1) / 4;
                        me->add_temp("apply/attack", count);
                        message_combatd(msg + HIC "$N" HIC "����$n" HIC
                                        "����һ��֮��������������"
                                        "��ǰԾ������ৡ�����������\n" NOR,
                                        me, target);
                        COMBAT_D->do_attack(me, target, weapon);
                        COMBAT_D->do_attack(me, target, weapon);
                        COMBAT_D->do_attack(me, target, weapon);
                        me->add_temp("apply/attack", -count);
                }
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, ap / 2, 66,
                                           HIR "$n" HIR "һ���ҽУ�������������"
                                           "��ʱð������Ѫ����\n" NOR);
                me->start_busy(3);
        } else
        {
                me->start_busy(2);
		if (is_yunv)
			msg += CYN "ȴ��$n" CYN "΢΢һЦ������һ�С���Ů�����������ɵص�ס��$N�Ľ��С�\n" NOR;
		else
	                msg += CYN "����$n" CYN "������$N" CYN "����ͼ��бԾ�ܿ���\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}

