// zhenwu.c ̫�������������а��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������а��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
                
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query("neili") < 200)
                return notify_fail("�����������������޷�ʹ�á���å���񡹡�\n");

        msg = HIY "$N" HIY "ͻȻ�齣����������ˣ��һ����ɫ���ţ�߳������ſ���������һ���޼�������$n" HIY "��\n" NOR;

        me->add("neili", -50);
        ap = me->query_skill("sword", 1) / 2 +
        me->query_skill("taiji-jian", 1);
        dp = target->query_skill("parry");
        if (target->is_bad()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIG "����$p" HIG "������$P" HIG "����ͼ����"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 3, me);
        target->receive_wound("jing", damage / 6, me);
        return
                HIR "$p" HIR "����ʧ�룬���ڵ�������$P"
                HIR "��һ�ƻ���Ҫ����������֮��������å����ֱ������ǰ����ʱ��֪��εֵ���\n" NOR;
}

