#include <ansi.h>
#include <combat.h>

#define HUI "��" HIY "��������" NOR "��"
#define HUIP "��" HIY "�����л�" HIW "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
		
		 if (me->query("str") < 54)
                return notify_fail("�����������������޷������������յĿ������ڡ�\n"); 

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/hui"))
                return notify_fail("����Ҫ��ѧ����п����лڡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUI "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("���ڹ���Ϊ����������ʩչ" HUI "��\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("��������Ϊ����������ʩչ" HUI "��\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 800)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" HUI "��\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" HUI "��\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" HUI "��\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("��������������������ʩչ" HUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ��һ��
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("dodge") + target->query("dex") * 10;

        message_sort(HIW "\n��Ȼ$N" HIW "���μ���������һ�������ֺ���һ��"
                     "����$n" HIW "�����ǽ���ʮ����" HUIP "����������֮��"
                     "˵���㵽������ɽ����֮����$n" HIW "��ӿ��ȥ������ʯ"
                     "���쾪�������ޱȡ�\n" NOR, me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(10),
                                          HIR "$P����һ�������ѻ���$p��ǰ��$p��"
                                          "���������ٱ��������С�\n" NOR);
        } else
        {
                msg = HIC "ȴ��$p����˫�ۣ�����Ӧ�ԣ�$P��"
                      "������ţ�뺣������жȥ��\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ���
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("parry") + target->query("int") * 10;

        message_sort(HIW "\n$N" HIW "һ�Ƽȳ���������Ȼ������$n" HIW "��"
                     "����֮�⣬������ǰ�������������ϲ�������һ��" HUIP
                     "��������������ŭ����ӿ���Ʋ��ɵ�����ʱ$p�����Ϣ��"
                     "�ͣ����㲻�ȡ�\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                          HIR "$pһ���Һ�����$P��һ�ƻ�����ǰ��"
                                          "���꿦����˼����߹ǡ�\n" NOR);
        } else
        {
                msg = HIC "����$pȫ���ֵ��мܣ�����������"
                      "�࣬��$P������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // ������
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("force") + target->query("con") * 10;

        message_sort(HIW "\n������$N" HIW "����б�ӣ�ǰ������δ����������"
                     "���ֵ�����Ȼ�ֹ���һ��" HUIP "���Ƽз��ƣ���������"
                     "����һ��������ǽ����ǰ�����ȥ��$n" HIW "ֻ����Ѫ��"
                     "ӿ����Ϣ���ǡ�\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIR "���$p����������$P�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg = HIC "$p�ۼ��������ͣ����μ��ˣ�˲��"
                      "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }
        message_vision(msg, me, target);
        me->add("neili", -400 - random(600));
		
		        // ��һ��
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("dodge") + target->query("dex") * 10;

        message_sort(HIW "\n$N" HIW "��Цһ��������$n" HIW "��Ӧ����ʱ���������ƣ�Я��籩��֮��Ϯ��$n" HIW "��\n" NOR, me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(10),
                                          HIR "$P����һ�������ѻ���$p��ǰ��$p��"
                                          "���������ٱ��������С�\n" NOR);
        } else
        {
                msg = HIC "ȴ��$p����˫�ۣ�����Ӧ�ԣ�$P��"
                      "������ţ�뺣������жȥ��\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ���
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("parry") + target->query("int") * 10;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                          HIR "$pһ���Һ�����$P��һ�ƻ�����ǰ��"
                                          "���꿦����˼����߹ǡ�\n" NOR);
        } else
        {
                msg = HIC "����$pȫ���ֵ��мܣ�����������"
                      "�࣬��$P������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // ������
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("force") + target->query("con") * 10;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIR "���$p����������$P�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg = HIC "$p�ۼ��������ͣ����μ��ˣ�˲��"
                      "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }
        message_vision(msg, me, target);
        me->add("neili", -400 - random(600));
		
		        // ��һ��
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("dodge") + target->query("dex") * 10;

        message_sort(HIW "\n�ۼ�$N" HIW "�������ƣ�����δ�ˣ������ֻ������ƣ�����$n" HIW "��һʱ��������գ������޹⡣\n" NOR, me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(10),
                                          HIR "$P����һ�������ѻ���$p��ǰ��$p��"
                                          "���������ٱ��������С�\n" NOR);
        } else
        {
                msg = HIC "ȴ��$p����˫�ۣ�����Ӧ�ԣ�$P��"
                      "������ţ�뺣������жȥ��\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ���
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("parry") + target->query("int") * 10;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                          HIR "$pһ���Һ�����$P��һ�ƻ�����ǰ��"
                                          "���꿦����˼����߹ǡ�\n" NOR);
        } else
        {
                msg = HIC "����$pȫ���ֵ��мܣ�����������"
                      "�࣬��$P������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // ������
        ap = me->query_skill("strike") + me->query("str") * 10 + me->query_skill("huimeng-xinfa", 1) / 2;
        dp = target->query_skill("force") + target->query("con") * 10;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIR "���$p����������$P�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg = HIC "$p�ۼ��������ͣ����μ��ˣ�˲��"
                      "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }
        message_vision(msg, me, target);
        me->add("neili", -400 - random(600));
		
		
		if ((int)me->query_skill("huimeng-xinfa", 1) > 600){
            me->start_busy(1 + random(2));
		}else{
			me->start_busy(3 + random(4));
        }
		return 1;
}
