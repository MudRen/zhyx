// po.c ̫��ȭ���ơ��־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ơ��־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�á��ơ��־���\n");         
                
        if ((int)me->query_skill("taiji-quan", 1) < 150)
                return notify_fail("���̫��ȭ������죬����ʹ�á��ơ��־���\n");
                                
        if ((int)me->query("neili", 1) < 200)
                return notify_fail("����������̫��������ʹ�á��ơ��־���\n");
                        
        msg = HIW "$N" HIW "Ĭ��̫���񹦣�ʹ��̫��ȭ���ơ��־���˫ȭ��������$n"
              HIW "��С����\n" NOR;
        me->add("neili", -100);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
                me->start_busy(3);
                target->start_busy(random(3));
                target->add("neili", -400);
                damage = (int)me->query_skill("force");
                damage += random(damage / 2) + me->query("jiali");
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 30,
                                           HIR "��һȭ����ƽ�����棬����������$n"
                                           HIR "���е���·��һȭ�������У�\n"
                                           ":����@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ������С��������ݿ���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

