#include <ansi.h>
#include <combat.h>

#define KU "��" HIW "�ຣ���Ļ�ͷ�ǰ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail(KU "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 800)
                return notify_fail("���ڹ���Ϊ����������ʩչ" KU "��\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("��������Ϊ����������ʩչ" KU "��\n");

        if ((int)me->query_skill("bluesea-force", 1) < 400)
                return notify_fail("���Ϻ�������򲻹�������ʩչ" KU "��\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("��û�м����Ϻ�����������ʩչ" KU "��\n");

        if (me->query_skill_prepared("strike") != "bluesea-force")
                return notify_fail("��û��׼���Ϻ�����������ʩչ" KU "��\n");

        if ((int)me->query("neili") < 1500)
                return notify_fail("��������������������ʩչ" KU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "��Ȼһ����Х��ʩ����" HIG "�ຣ���Ļ�ͷ�ǰ�"
              HIW "����˫�Ʒ�����������Ӱ����������$n" HIW "��\n" NOR;  

        ap = me->query_skill("strike") + me->query("str") * 100;
        dp = target->query_skill("force") + target->query("str") * 100;

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 400,
                                           HIR "$n" HIR "���Ʋ�͸������ʵ��$N" HIR
                                           "˫������$p" HIR "ǰ�أ������꿦�ꡱ��"
                                           "�����������߹ǡ�\n" NOR);
	        message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "�������ƷǷ�������"
                       "�����мܣ�����������Ծ������\n" NOR;
	        message_combatd(msg, me, target);
        }

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
        	COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add("neili", -500);
        me->start_busy(4 + random(3));
        return 1;
}

