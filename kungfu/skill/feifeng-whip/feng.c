// feng.c �ﳯ��
// looo/2001/6/28
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int count;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "�ﳯ��ֻ����ս����ʹ��\n");


        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");


        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ����������ʹ�á��ﳯ�ˡ���\n");

        if (me->query_skill("feifeng-whip", 1) < 150)
                return notify_fail("��ķɷ�޷���Ϊ������Ŀǰ����ʹ�á��ﳯ�ˡ���\n");

        if (me->query("neili") < 500)
                return notify_fail("��������������޷�ʹ�á��ﳯ�ˡ���\n");

        if (me->query_skill_mapped("whip") != "feifeng-whip")
                return notify_fail("��û�����ɷ�޷�������ʹ�á��ﳯ�ˡ���\n");

        msg = HIY "$N" HIY "����" HIY "$n" HIY "��٬һЦ����ǰ����,����" + weapon->name() +
              HIY "ȴ����ͣ����һ�С��ﳯ�ˡ�\n"
              HIY "���ϴ�գ�����Ϸ��"
              HIY "���������ֵ�" HIY "$n" HIY "����!! \n" NOR;

        ap = me->query_skill("whip") + 100;
        if (living(target))
                 dp = target->query_skill("parry");
        else     dp = 0;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "���$p" HIR "��$P" HIR
                       "���˸����ֲ�����Ŀ�Ӳ�Ͼ��ƣ�ڱ�����\n" NOR;
                count = ap;

                me->add_temp("apply/attack", count);

        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "���ƺ�����������Ȼ������Ӧ����\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        me->add("neili", -150);
        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(5));
        return 1;
}
