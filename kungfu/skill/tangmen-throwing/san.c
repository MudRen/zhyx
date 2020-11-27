#include <ansi.h>
#include <combat.h>

#define HUA "��" HIM "ɢ������" NOR "��"
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string pmsg;
        string msg;
        object weapon;

        if (playerp(me) && ! me->query("can_perform/tangmen-throwing/san"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" HUA "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            ((string)weapon->query("id") != "sanhua tianyu" &&
            (string)weapon->query("skill_type") != "throwing"))
                return notify_fail("����������û�����Ű���ɢ����Ů������ʩչ" HUA "��\n");

        if ((string)weapon->query("id") != "sanhua tianyu" &&
             weapon->query_amount() < 10)             
                return notify_fail("����������û���㹻�İ���������ʩչ" HUA "��\n");
                
        if ((skill = me->query_skill("tangmen-throwing", 1)) < 160)
                return notify_fail("������Ű���������죬����ʩչ" HUA "��\n");
                
        if ((int)me->query_skill("boyun-suowu", 1) < 160)
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

        msg = HIG "$N" HIG "���п�סһö" + weapon->name() + HIG"���������˵Ĺ��������弱����ת����������һ����Х�����磡\n" NOR
              HIG "ͻȻ�������зɳ�������" HIC "����" NOR + HIG "������һ�������������ķ���$n" HIG "�����壡\n" NOR;

        ap = me->query_skill("throwing") + me->query_skill("force") + me->query_skill("dodge") + me->query_skill("martial-cognize",1); 
        dp = target->query_skill("parry") + target->query_skill("dugu-jiujian", 1); 
        
        message_combatd(msg, me, target);
        tell_object(target, HIR "\n�㼱æ��������ϣ���ܹ��м���������һ����\n"NOR);
        if (ap * 3 / 4 + random(ap / 2) > dp)
        {
                if (weapon->query("id") != "sanhua tianyu")
                {
                        n = 10;                        
                        weapon->add_amount(-10);
                        damage = ap * 4;
                        msg = HIR "���$p" HIR "һ���Һ���������$P" HIR "������ʮ" +
                                weapon->query("base_unit") + weapon->name() + HIR "��\n" NOR;

                        while (n--)
                        {
                                COMBAT_D->clear_ahinfo();
                                weapon->hit_ob(me, target,
                                               me->query("jiali") + 100 + n * 10);
                        }

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
                msg = HIR "��Ȼ�������Ĺ�Ӱһ����û��$n����һ�٣����һ����Ѫ�����������\n" NOR;
                message_combatd(msg, me, target);
                tell_object(target, HIR "��ֻ�����ؿ�һ�����ĵ���ʹ����ͷһ��ֻ��������ö�����Ѿ������Ƕ������Ŀڡ�\n"
                                    "Ѫ������Լ�м���С��[ɢ������...]��\n"NOR);
                weapon->hit_ob(me, target, me->query("jiali") + 200); 
                weapon->move(target);
                
                target->receive_wound("qi", 1, me);
                COMBAT_D->clear_ahinfo();
                target->die(me);
                me->start_busy(3);
        } else
        {
                tell_object(target, HIR "��Ȼ�������Ĺ�Ӱһ����û��������һ����æ��������ȫ����\n" NOR);
                msg = HIR "$n" HIR "˫�ۼ��裬��������Ʒ�֮����ֻ������һ�����죬����������ö�����ķɿ�ȥ��\n" NOR;
                message_combatd(msg, me, target);
                if ( target->query("neili") < 1000 )
                        target->set("neili", 0);
                else
                        target->add("neili", -1000);
                weapon->move(environment(me));
                me->start_busy(4);
        }
        return 1;
}

