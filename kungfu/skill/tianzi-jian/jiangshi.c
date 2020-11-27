#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define JIANGSHI "��" HIW "���ӽ���" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        object weapon;

        if (userp(me) && ! me->query("can_perform/tianzi-jian/jiangshi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIANGSHI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JIANGSHI "��\n");

        if (me->query_skill_mapped("sword") != "tianzi-jian") 
                return notify_fail("��û�м������ӽ���������ʩչ" JIANGSHI "��\n"); 
 
        if (me->query_skill("tianzi-jian", 1) < 150)
                return notify_fail("������ӽ�����������죬����ʩչ" JIANGSHI "��\n");

        if (me->query("neili") < 400)
                return notify_fail("�����������������ʩչ" JIANGSHI "��\n");
 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "\n$N" HIG "������������������벻��֮����"
              "$n" HIG"ֱ�̹������������ֳ����߰�����\n" NOR;
 
        ap = me->query_skill("tianzi-jian", 1) * 2  +              
             me->query_skill("martial-cognize", 1);

        dp = target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

        me->add("neili", -150);

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "�ҿ�$n" HIY "ȫ���������Ž�$N" HIY
                       "��һ�л��⡣\n" NOR;
	         me->start_busy(2);
        } else
        {
                me->add("neili", -200);
	         me->start_busy(3);
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(5),
                                           HIR "$n" HIR "��æ�����ܣ�Ȼ����һ�����ù���"
                                          "��ֻ��$n" HIR "һ���ҽУ���һ���Ѵ���$n��" HIR "��"
                                          "ʱ��Ѫ�ɽ���\n" NOR); 
        }
        message_sort(msg, me, target);
        return 1;
}

