#include <ansi.h>
#include <combat.h>

#define TIAN "��" HIW "�������" NOR "��"
#define TIANA "��" HIR "�����л�" HIW "��"
#define TIANB "��" HIG "�𾪰���" HIW "��"
#define TIANC "��" HIB "˫��ȡˮ" HIW "��"
#define TIAND "��" HIY "��������" HIW "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i, count;

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/hui"))
                return notify_fail("����δѧ�ᡸ"HIR"�����л�"NOR"���޷����"TIAN"��\n");

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/zhen"))
                return notify_fail("����δѧ�ᡸ"HIG"�𾪰���"NOR"���޷����"TIAN"��\n");

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/qu"))
                return notify_fail("����δѧ�ᡸ"HIB"˫��ȡˮ"NOR"���޷����"TIAN"��\n");

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/fei"))
                return notify_fail("����δѧ�ᡸ"HIY"��������"NOR"���޷����"TIAN"��\n");

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷����˾��У�\n");

        if ((int)me->query("str") < 46)
                return notify_fail("���������������������ʩչ"TIAN"��\n");

        if ((int)me->query("con") < 42)
                return notify_fail("��������������������ʩչ"TIAN"��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(TIAN "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("���ڹ���Ϊ����������ʩչ" TIAN "��\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("��������Ϊ����������ʩչ" TIAN "��\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 400)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" TIAN "��\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" TIAN "��\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" TIAN "��\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("��������������������ʩչ" TIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ��һ��
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("dodge") + target->query("dex") * 15;

        message_sort(HIW "\n��Ȼ$N" HIW "���μ���������һ�������־�ʹ��һ��"
		    TIANA "����ɽ����֮����$n" HIW "��ӿ��ȥ��\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(20),
                                          HIR "$N����һ�������ѻ���$n��ǰ��$n��"
                                          "���������ٱ��������С�\n" NOR);
        } else
        {
                msg = HIC "ȴ��$n����˫�ۣ�����Ӧ�ԣ�$N��"
                      "������ţ�뺣������жȥ��\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ���
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query("str") * 15;

        message_sort(HIW "\n$N" HIW "һ�Ƽȳ���������Ȼ������$n" HIW "һ"
                     "��֮�⣬������ǰ�������������ϲ���ʹ��" TIANB
                     "����һ�а����$n" HIW "��\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "$nһ���Һ�����$N��һ�ƻ�����ǰ��"
                                          "���꿦����˼����߹ǡ�\n" NOR);
        } else
        {
                msg = HIC "����$nȫ���ֵ��мܣ�����������"
                      "�࣬��$N������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // ������
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("force") + target->query("con") * 15;

        message_sort(HIW "\n������$N" HIW "����б�ӣ�ǰ������δ����������"
                     "���ֵ���һʽ" TIANC "˫�����»ζ�����һ��������"
		     "ǽ����$n" HIW "�����ȥ��\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "���$n����������$N�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg = HIC "$n�ۼ��������ͣ����μ��ˣ�˲��"
                      "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }
        message_vision(msg, me, target);

        // ����
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query("int") * 15;

        msg = HIW "\n$N" HIW "�������ƺ�ͻȻԾ�����У��Ӹ�����ʹ��" TIAND "˫�Ʒ�������$n"HIW"��\n" NOR;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "���$N" HIR "����ɽ������Ĺ�"
                       "�ƣ���ȫ�޷��ֵ����м�ɢ�ң������˺�\n" NOR;
                count = ap / 8;
        } else
        {
                msg += HIC "$n" HIC "�ĵ�΢΢һ������֪�����æ"
                       "�������񣬽߾����ܻ���$N" HIC "����������\n" NOR;
                count = ap / 20;
        }
        message_vision(msg, me, target);

        me->add_temp("apply/attack", count);
        me->add_temp("apply/unarmed_damage", count / 2);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
	target->start_busy(3 + random(5));
        me->add("neili", -2000 - random(1000));
        me->start_busy(3 + random(5));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 2);

        return 1;
}
