#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

#define MIESHI "��" HIR "����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, clv, str;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/canhe-zhi/mieshi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(MIESHI "ֻ����ս���жԶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ��" MIESHI "��\n");

        clv = me->query_skill("canhe-zhi", 1);

        if (clv < 800)
                return notify_fail("��Ĳκ�ָ��Ϊ���ޣ�����ʩչ" MIESHI "��\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("������û��׼��ʹ�òκ�ָ������ʩչ" MIESHI "��\n");

        if (me->query_skill("zihui-xinfa", 1) < 500)
                return notify_fail("����ϻ��ķ���Ϊ����������ʩչ" MIESHI "��\n");

        if ((int)me->query("max_neili") < 16000)
                return notify_fail("���������Ϊ���㣬����ʩչ" MIESHI "��\n");

        if (me->query("con") < 51)
                return notify_fail("����������̫�ͣ�����ʩչ" MIESHI "��\n"); 

        if (me->query("str") < 47)
                return notify_fail("����������̫�ͣ�����ʩչ" MIESHI "��\n"); 

        if (me->query("neili") < 2000)
                return notify_fail("�����������������ʩչ" MIESHI "��\n");
                
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

                    message_vision(HIR"$NХ�����������Ƴ��죬������ָ֮����ʩչ���κ�ָ���վ��� �� �� �� ������\n"NOR, me);

        ap = clv + me->query_skill("parry") + me->query_skill("zihui-xinfa", 1) + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge") + target->query_skill("parry") + target->query_skill("martial-cognize", 1);

                damage = ap * 3 / 2 + random(ap*3/2);

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           MAG "����������������Ծ׷���������������ų�һ�ߣ��˷����˶�������\n"NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           MAG "ǰ��δƽ���ڶ��㽣��������������������к���������ʽ����壬���ȶ�������\n" NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           MAG "���ؽ����༤����������ӿ��������ɽ�����ѣ���������ľ��ˣ��ݿ����࣡��\n" NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           MAG "��������������������ܾ���ʨͻأ���𣬶����ɸ�ˮ���������׷ɣ���ˮ��������\n" NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           MAG "������������������ɽ������ѩ����ҡ����̣�������Х������������Ծ������η��ף����ò�Ϣ����\n" NOR);
        message_combatd(msg, me, target);

        if (ap + random(ap) > dp)
        {
                target->set("neili",0); 
                me->start_busy(3+random(3)); 
                if (random(3) > 1)
                {
                me->add("neili", -1000); 
                target->receive_damage("qi", damage*2, me); 
                target->receive_wound("qi", damage, me);
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                msg = HIR "$N���һʽ��������������ӿ��������͸$n" HIR "�����壬ֻ���½������ƿ�֮���� 
$n"HIR"������ͻȻ��¶��Ī���Ŀ־壬���еľ����ѱ��֧�����飬 
"HBMAG"$n����֮�ʣ����ﱻ���ɽ����ᴩ��������ʱѪ����ע��ȫ��������ʧ��\n" NOR;
                msg += "($n"+str+")\n";
                } else
                {
                damage = ap * 2 + random(ap*2);
                me->add("neili", -500); 
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$N���һʽ��������������ӿ��������͸$n"HIR"�����壬ֻ���½������ƿ�֮����
$n"HIR"������ͻȻ��¶��Ī���Ŀ־壬���еľ����ѱ��֧�����飬
$n"HIR"����֮�ʣ����ﱻ���ɽ����ᴩ��������ʱѪ����ע��ȫ��������ʧ��\n" NOR); 
                 }
        } else
        {
                me->add("neili", -800);
                me->start_busy(3+random(4));
                msg = CYN "$n" CYN "��$P" CYN "������ӿ���������׵�"
                       "������æ������Ų������������\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}


