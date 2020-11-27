#include <ansi.h>
#include <combat.h>

#define HUA "��" HIR "�ƻ�" NOR "��"

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string msg;
        object weapon;

        if (playerp(me) && ! me->query("can_perform/tangmen-throwing/hua"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" HUA "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            ((string)weapon->query("id") != "tang hua" &&
            (string)weapon->query("skill_type") != "throwing"))
                return notify_fail("����������û�����Ű����ƻ�������ʩչ" HUA "��\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 180)
                return notify_fail("������Ű���������죬����ʩչ" HUA "��\n");

        if ((int)me->query_skill("boyun-suowu", 1) < 180)
                return notify_fail("��Ĳ�������������죬�޷�ʩչ" HUA "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" HUA "��\n");

        if ((int)me->query("max_neili") < 1200)
                return notify_fail("���������Ϊ���㣬����ʩչ" HUA "��\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������㣬����ʩչ" HUA "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -100);

        msg = HIR "\n$N" HIR "����ͻȻ����һ֧�����������ޣ�$n" HIR "�����е���ˣ�\n$N" HIR "��$n" HIR "һЦ��һ������$n"HIR "��ȥ��\n" +
              HIG "ֻ���ǻ����ˣ�������棬���뻨�����ɷ�Ǻÿ���\n" NOR;

        ap = me->query_skill("throwing") + me->query("dex") * 20 + me->query_skill("dodge");
        dp = target->query_skill("dodge") + target->query_skill("dugu-jiujian", 1); 

        message_combatd(msg, me, target);
        tell_object(target, HIC "\n�㼱æ�����ȥ�ӣ���ͻ�أ��㷢�����죬����һ������������һԾ��\n" NOR);
        if (ap * 2 / 3 + random(ap * 3 / 2) > dp)
        {
                if (target->query("reborn") || weapon->query("id") != "tang hua")
                {
                        string pmsg;

                        weapon->add_amount(-1);
                        damage = ap * 4;
                        msg = HIR "���$p" HIR "һ���Һ���������$P" HIR "������һ" +
                                weapon->query("base_unit") + weapon->name() + HIR "��\n" NOR;

                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target, me->query("jiali") + 120);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage, me);

                        p = (int)target->query("qi") * 100 / (int)target->query("max_qi");

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);
                        me->start_busy(2);
                        return 1;
                }
                
                msg = HIR"�ǻ�Խ��Խ�ޣ�$n" HIR "��֪�������ѳ����ˣ�����һ��,΢Ц�ŵ����ˣ��ǻ�Ҳл�ˡ�\n" NOR;
                tell_object(target, HIR "\n�㿴���ǻ���������һ��������\n���������������ժ��������"
                                        "�ǻ�������Խ��Խ���ˣ���ϡ����ǵ���������һ��СС�ġ��ơ��֡�\n" NOR);
                weapon->hit_ob(me, target, me->query("jiali") + 200);
                weapon->move(target);

                message_combatd(msg, me, target);
                target->receive_wound("qi", 1, me);
                COMBAT_D->clear_ahinfo();
                target->unconcious();
                me->start_busy(2);
        } else
        {
                if (weapon->query("id") == "tang hua")
                        tell_object(target, HIR "�������ƻ��������е��ƻ���������ȫ���������������ӵĸ�����\n" NOR);
                msg = HIR "$n " HIR "����Ʈ�����ǻ����ն�����ֻ������һ�����죬�ǻ�л�ˣ���������ڵ����ϡ�\n" NOR;
                message_combatd(msg, me, target);
                if ( target->query("neili") < 1000 )
                        target->set("neili", 0);
                else
                        target->add("neili", -1000);
                weapon->move(environment(me));
                me->start_busy(3);
        }
        return 1;
}

