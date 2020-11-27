#include <ansi.h>
#include <combat.h>

#define XIAN "��" HIY "��ʱ������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/moon-blade/yue"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" XIAN "��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" XIAN "��\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" XIAN "��\n");

        if ((int)me->query_skill("moon-blade", 1) < 120)
                return notify_fail("���Բ���䵶�������ң�����ʩչ" XIAN "��\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("��û�м���Բ���䵶������ʩչ" XIAN "��\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�����������������ʩչ" XIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        
        msg = HIY "$N" HIY "������գ�����˸���������ߵ���ÿ������$n" HIY "���ò�ȫ��Ӧ����\n"
              "ÿ��������ʵ��׾��ƫ���У����µ��յĸо���\n"
              "�ҵ��������$n" HIY "�����α仯�����ǰ�$n" HIY "��ͨ��͸һ�㣡\n" NOR;
        
        ap = me->query_skill("blade") + me->query_skill("force") + me->query_skill("dodge") + me->query_skill("martial-cognize",1);
        dp = target->query_skill("dodge") + target->query_skill("blade");
             
        if (ap / 2 + random(ap) > dp)
        {
                damage = me->query_skill("blade") + me->query_skill("force");
                damage *= 3;
                me->add("neili", -150);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 150,
                                           HIR "��ʱһ�ɱ����ĵ����ӹ�ȫ��$n" 
                                           HIR "ȫ���ʱ��Ѫ���죬ҡҡ������\n" NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap * 2) > dp && ! target->is_busy())
                        target->start_busy(5 + random(10));
        } else 
        {
                msg += CYN "$p" CYN "���һ����Ҳ���мܣ��������"
                       "�������ߣ��ܿ���$P" CYN "��һ�С�\n" NOR;
                me->add("neili", -50);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

