//���߽�--���߿��� 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���߿���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ�������죬����ʹ�ý��߿��衣\n");

        if ((int)me->query_skill("jinshe-jian", 1) < 150)
                return notify_fail("��Ľ��߽���������죬����ʹ�ý��߿��衣\n");


        if ((int)me->query("neili", 1) < 400)
                return notify_fail("����������̫��������ʹ�ý��߿��衣\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("��û�м������߽���������ʹ�ý��߿��衣\n");

        msg = HIY "$N" HIY "���²���ϸ�룬���潣�ߣ��������,ʹ��һ�С����߿��衱��"
              "���е�" + weapon->name() + HIY "�ӳ����������Ľ���,��Ӱ����,����ֹЪ!��\n" NOR;
        if (random(me->query_skill("sword")) > target->query_skill("parry") / 3 || !living(target))
        {
                me->start_busy(2);
                target->start_busy(1 + random(2));

                damage = (int)me->query_skill("sword", 1) +
                         (int)me->query_skill("jinshe-jian", 1);
          damage = damage / 2 + random(damage);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                       HIR "����һ��," HIR "$n" HIR "���ؿں�Ȼ����һ������Ѫ��! \n" NOR);

                                         
        } else
        {
                me->start_busy(3);
                msg += CYN "$p" CYN "�Ʋ��������·��������ֻ����������! \n" NOR;
                      
        }
        message_combatd(msg, me, target);

        return 1;
}
