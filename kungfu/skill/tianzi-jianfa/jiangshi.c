#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define JIANGSHI "��" HIW "���ӽ���" NOR "��"

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        object weapon;

        if (userp(me) && ! me->query("can_perform/tianzi-jianfa/jiangshi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIANGSHI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JIANGSHI "��\n");

        if (me->query_skill_mapped("sword") != "tianzi-jianfa") 
                return notify_fail("��û�м������ӽ���������ʩչ" JIANGSHI "��\n"); 
 
        if (me->query_skill("tianzi-jianfa", 1) < 200)
                return notify_fail("������ӽ�����������죬����ʩչ" JIANGSHI "��\n");

        if (me->query("neili") < 600)
                return notify_fail("�����������������ʩչ" JIANGSHI "��\n");
 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "\n$N" HIG "������������������벻��֮����"
              HIG "$nֱ�̹���" HIG "��\n" NOR;
 
        ap = me->query_skill("tianzi-jianfa", 1) * 2 + 
             me->query_skill("sword", 1) +
             me->query_skill("martial-cognize", 1);

        dp = target->query_skill("force") + target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

        me->add("neili", -150);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;
	        me->start_busy(2);
        } else
        {
                me->add("neili", -200);
	        me->start_busy(3);
                damage = ap + random(ap);
                target->add("neili", -(me->query_skill("tianzi-jianfa", 1) + 
                            random(me->query_skill("tianzi-jianfa", 1))), me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(5),
                                           (: final, me, target, damage :));

        }
        message_sort(msg, me, target);
        return 1;
}


string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 3, me);
        target->busy(1);
        return  HIR "$n" HIR "��æ�����ܣ�Ȼ����һ�����ù���"
                "��ֻ��$p" HIR "һ���ҽУ���һ���Ѵ���$n��" HIR "��"
                "ʱ��Ѫ�ɽ���������ɢ��\n" NOR;
}