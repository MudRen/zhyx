// an.c ̫��ȭ�������־�
// Modify by haiyan

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, acter, ap, dp, taoism;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/taiji-quan/an")) 
                return notify_fail("�㻹����ʹ�á������־���\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�á������־���\n"); 
                
        if ((int)me->query_skill("taiji-quan", 1) < 400)
                return notify_fail("���̫��ȭ�����⻹����������ʹ�á������־���\n");
                                
        if ((int)me->query("neili", 1) < 300)
                return notify_fail("����������̫��������ʹ�á������־���\n");
                        
        msg = HIG "$N" HIG "˫ȭ���»Ӷ���ʹ��̫��ȭ�������־���$n"
              HIG "�е�һ��ǿ��ľ�����ͷ��ѹ�䡣\n" NOR;

        me->add("neili", -200);

        dp = (target->query_skill("force", 1) +
              target->query_skill("parry", 1) +
              target->query_skill("martial-cognize", 1)) / 3;

        if (me->query("character") == "��������" || me->query("character") == "������")
               acter = 4;
        else
               acter = 5;

        taoism = me->query_skill("taoism", 1);
        if (taoism > 1000) taoism = 1000;
        
        ap = (me->query_skill("taiji-shengong", 1) +
              me->query_skill("taiji-quan", 1) +
              me->query_skill("martial-cognize", 1) +
              taoism) / acter;

        if (target->is_bad())   ap += ap / 4;

        if (random(ap) > dp / 2 || !living(target))
        {
                me->start_busy(3);
                target->start_busy(random(3));

                damage = ap * 10;

                if (me->query("shen") / 800 > 5000)
                     damage += 5000;
                else
                     damage += me->query("shen") / 800;

                damage /= 2;

                damage += me->query("jiali") * 2;
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 70,
                                           HIY "$n" HIY "�Ǹк��������������ѵ���"
                                           HIY "��ͷһ�𣬿�������"HIR"��Ѫ"HIY"��\n"
                                           ":����@?");
        } else 
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "�����ڹ����۾����⣬ͦ��Ӳ����$P"
                       HIY "��һ�У����顱��һ�����죬˫����������������\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

