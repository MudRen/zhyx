// tianwai.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
                return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( me->query_skill_mapped("sword") != "yuxiao-jian") 
                return notify_fail("�㲢û��ʹ�����｣����\n"); 

        if (me->query_skill("bibo-shengong", 1) < 120)
                return notify_fail("��ı̲��񹦵ȼ�����, ����ʹ�á�������������\n");

        skill = me->query_skill("yuxiao-jian",1);

        if (skill < 100)
                return notify_fail("������｣���ȼ�����, ����ʹ�á�������������\n");

        if (me->query("neili") < 200)
                return notify_fail("��������������޷����á�������������\n");

        msg = HIC "$N" HIC "һ����Х����������" + weapon->name() + HIC +
              "������ֹ����Ӱ��ҹĻ������$n" HIC "��\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("force");
        if (dp < 1) dp = 1;
        if (ap / 2 + random(ap) > dp * 3 / 4 || !living(target))
        {
                    me->add("neili", -300);
                qi_wound = (int)me->query_skill("sword") +
                           (int)me->query_skill("bibo-shengong", 1);
                qi_wound = qi_wound / 2 + random(qi_wound / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, qi_wound, 66,
                                           HIR "$n" HIR "��ʱ������ǰ�����������˫������"
                                           "��������֪����һ���ʹ������һ�㣡\n" NOR);
                me->start_busy(1 + random(3));
                target->start_busy(1 + random(2));
        } else
        {
                me->add("neili", -50);
                msg += HIG "����$n" HIG "���ľ��������ֻ�������$N"
                       HIG "������Ʋ��һ�ߡ�\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
