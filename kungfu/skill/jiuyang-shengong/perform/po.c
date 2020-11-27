#include <ansi.h>
#include <combat.h>

#define PO "��" HIY "��������" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/jiuyang-shengong/po"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (userp(me) && ! me->query("can_learn/jiuyang-shengong/enable_weapon"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");    

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" PO "��\n");

        if ((int)me->query_skill("jiuyang-shengong", 1) < 220)
                return notify_fail("��ľ����񹦲�����죬����ʩչ" PO "��\n");

        if ((int)me->query_skill("force", 1) < 240)
                return notify_fail("����ڹ���������������ʩչ" PO "��\n");

        if ((int)me->query_skill("sword", 1) < 240)
                return notify_fail("��Ļ���������򲻹�������ʩչ" PO "��\n");

        if ((int)me->query("max_neili") < 5500)
                return notify_fail("���������Ϊ���㣬����ʩչ" PO "��\n");

        if (me->query("neili") < 400)
                return notify_fail("��������������������ʩչ" PO "��\n");

        if (me->query_skill_mapped("sword") != "jiuyang-shengong") 
                return notify_fail("��û�м���������Ϊ����������ʩչ" PO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "\n$N" HIY "һ���������������ǣ�ȫ���������뽣��������" + weapon->name() + HIY 
              "��â���䣬ɲ�Ǽ�һ��ǿ���Ľ�����ӿ��$n" HIY "��\n" NOR;

        me->add("neili", -150);
        ap = me->query_skill("sword") + me->query_skill("force", 1);
        dp = target->query_skill("parry") + target->query_skill("force", 1);

        me->start_busy(2 + random(2));
        if (ap  + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85 + random(5),
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "����$n" HIC "��͸$P" HIC "����֮�е���������"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->add("neili", -(damage / 4));
        target->add("neili", -(damage / 8));
        return  HIY "$n" HIY "�����п����ޱȣ����޴Ӷ�����ֻ�÷����мܣ���������$N" HIY 
                "�������ˣ�һ�ɽ����Ѿ���͸$n" HIY "�ؿڣ���Ѫ��к������$n" HIY "�پ�"
                "��Ϣɢ�ҡ�\n" NOR;
}
