#include <ansi.h>
#include <combat.h>

#define SHA "��" HIW "����ɲ��" NOR "��"
#define JUAA "��" HIR "ն�ɾ�" HIY "��"
#define JUAB "��" HIG "���ɾ�" HIM "��"
#define JUAC "��" HIB "¾�ɾ�" HIC "��"
#define JUAD "��" HIY "����������" HIW "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(SHA "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force",1) < 400)
                return notify_fail("���ڹ���Ϊ����������ʩչ" SHA "��\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("��������Ϊ����������ʩչ" SHA "��\n");

        if ((int)me->query_skill("bluesea-force", 1) < 400)
                return notify_fail("���Ϻ�������򲻹�������ʩչ" SHA "��\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("��û�м����Ϻ�����Ϊ�Ʒ�������ʩչ" SHA "��\n");

        if (me->query_skill_mapped("force") != "bluesea-force")
                return notify_fail("��û�м����Ϻ�����Ϊ�ڹ�������ʩչ" SHA "��\n");

        if (me->query_skill_prepared("strike") != "bluesea-force")
                return notify_fail("��û��׼���Ϻ�����������ʩչ" SHA "��\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("��������������������ʩչ" SHA "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ��һ��
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("dodge",1) + target->query_skill("martial-cognize",1);

        if (me->query_skill("bluesea-force",1)>500) me->set_skill("count", 300);
        if (me->query_skill("bluesea-force", 1) > 600) 
                      { 
                              target->map_skill("dodge", 0); 
                      } 

        message_sort(HIY "\nֻ��$N" HIY "�������£�ٿ��һ���ĳ�������һ��"
		    JUAA "������֮������$n" HIY "��\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 4);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(20),
                                          HIR "$n" HIR "��һ��ԥ������һ�ƻ���"
                                           "�����У��������˼���������һ�ص�Ѫ��\n" NOR);
        } else
        {
                msg = HIG "Ȼ��$n" HIG "������$N" HIG
                       "�����ƣ����Ų�æ�Ķ������һ����\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ���
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query_skill("martial-cognize",1);

        message_sort(HIM "\n������$N" HIM "�ڿն��𣬺���ʹ��һ��" JUAB "����Ӱ�����������һ�����$n"
              HIM "�ٶȿ�Ĳ���˼�飡\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 4);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "$n" HIR "����˼����һ�Ƶĺ��ƣ���������"
                                           "��ǰ��ֻ�����ۡ���һ����$n��Ѫ���ߣ�\n" NOR);
        } else
        {
                msg = HIG "Ȼ��$n" HIG "������$N" HIG
                       "�����ƣ����Ų�æ�Ķ������һ����\n" NOR;
        }
        message_vision(msg, me, target);

        // ������
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("force") + target->query_skill("martial-cognize",1);

        message_sort(HIC "\n$N" HIC "���ƺ���ͣ�ͣ�������" JUAC "Я����֮������Ѹ�ײ����ڶ�֮��"
                     "��Ȼ��$n" HIC "��Ȼ�ĳ���\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 4);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "$n" HIR "�������ԣ��˹��ֵ���ֻ����$N��������"
                                           "��֮����ֱ�������澭��������ʱ��Ѫ���ѣ�\n" NOR);
        } else
        {
                msg = HIG "Ȼ��$n" HIG "������$N" HIG
                       "�����ƣ����Ų�æ�Ķ������һ����\n" NOR;
        }
        if (me->query_skill("count",1)>0) me->delete_skill("count"); 
        message_vision(msg, me, target);

        // ����
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query_skill("martial-cognize",1);

        msg = HIW "\n$N" HIW "��Цһ����˫�����Ữ�˸�Ȧ�ӣ����κ�Ȼ��죬ٿ��ʹ��" JUAD "����������Ӱ���˰���$n"HIW"��ȥ��\n" NOR;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIY "��������֮�£�$n" HIY "��ʱ���ú���"
                       "����������������ѹ��������ܣ�ֻ��$N"
                       HIY "һ�ƽ�һ�ƵĹ��������纣�ˡ�\n" NOR;
                count = ap / 8;
        } else
        {
                msg += CYN "$n" CYN "��������죬ֻ���������������ֵ���\n" NOR;
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
        me->add("neili", -1000 - random(500));
        me->start_busy(3 + random(5));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 2);

        return 1;
}
