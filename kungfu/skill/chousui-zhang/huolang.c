// ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object du;
        int damage;
        int ap, dpa, dpb;
        string msg,str;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʩչ���ˡ�\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 220)
                return notify_fail("��ĳ����ƻ�򲻹���\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�ó����ơ�\n");

        if (!(me->query_skill_mapped("strike") == "chousui-zhang"))
                return notify_fail("�㲢û�м��������ƣ�����û��ˣ�\n");

        if (!(me->query_skill_prepared("strike") == "chousui-zhang"))
                return notify_fail("�㲢û��׼�������ƣ�����û��ˣ�\n");

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("��Ļ���������򲻹���\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 220)
                return notify_fail("��Ļ����󷨻�򲻹���\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("���������Ϊ���㣬�޷�������ʩչ���ˡ�\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("��������Ϣ���㣬�޷�������ʩչ���ˡ�\n");


        if (! objectp(du = me->query_temp("handing")))
                return notify_fail("������Ҫ����(hand)һЩ��ҩ��Ϊ���ӡ�\n");

        if (! mapp(du->query("poison")))
                return notify_fail(du->name() + "�ֲ��Ƕ�ҩ���޷���������棿\n");

        msg = HIR "ֻ��$N" HIR "˫ĿѪ�죬ͷ��ɢ�ң��͵����췢��һ����Х��\n\n"
              "$N" HIR "����һ�ᣬ���Լ�������һҧ��������������"
              "���������ʱֻ��������Ѫ���������ȳ��ޱȣ��漴��\n"
              "��$N" HIR "����������ž����һ���죬˫��˳�������"
              "Ѫ��һ�ƣ�ɲ�Ǽ�һ�������ߵ��涾��ǽ�εض��𣬴�\n"
              "����ɽ����֮����$n" HIR "ӿȥ��\n\n" NOR;
        me->start_busy(4 + random(4));
        me->set("neili", 0);
        me->add("max_neili", -50);

        lvl = me->query_skill("chousui-zhang", 1);
        damage = 1000 + random(lvl*4);

        if (living(target))
             dpa = target->query("max_neili") * 3 / 2;
        else dpa = 0;

        if (me->query("max_neili") * 2 + random(me->query("max_neili")) < dpa)
        {
                msg += WHT "$n" WHT "��״��æ����������˫����"
                       "���Ƴ����Ʒ����ȣ�ǿ���������ʱ������"
                       "�εõ�ת����Ȼ��ͷ��$N" WHT "��ȥ��\n\n" NOR;
                msg += HIR "$N" HIR "һ����Ц����̾һ������ǰһ�ڣ������˵��ϡ�\n\n" NOR;
                me->add("max_neili", -random(50));
                me->receive_damage("qi",1,target);
                me->unconcious(); 

        } else
        {
                ap = me->query_skill("poison", 1) / 2 +
                     me->query_skill("force");
                if (living(target))
                     dpb = target->query_skill("dodge") * 3 / 2;
                else dpb = 0;
                if (ap + random(ap) < dpb)
                {
                        msg += CYN "$n" CYN "���Ʋ����æ��Ų���Σ��ܿ���$N" CYN "�Ĺ�����\n" NOR;
                        me->add("max_neili", -random(50));
                        target->start_busy(2);
                } else
                {
                        msg += HIR "$n" HIR "��������������ӿ����ֻ����ǰһƬͨ�죬"
                               "�ѱ�������ˣ�����ϯ��ȫ������ͷ��Ҫ����һ�㡣\n" NOR;
                        me->add("max_neili", -random(50));
                        target->affect_by("fire_poison",
                                       ([ "level" : me->query("jiali") * 3 + random(me->query("jiali") * 2),
                                          "id"    : me->query("id"),
                                          "duration" : lvl / 20 + random(lvl) ]));
                        target->receive_damage("qi", damage * 4 , me);
                        target->receive_wound("qi", damage * 2 , me);
                        target->receive_damage("jing", damage * 2, me);
                        target->receive_wound("jing", damage, me);
                        target->start_busy(10);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        msg += "($n"+str+")\n";
                }
        }

        destruct(du);
        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);

        return 1;
}

