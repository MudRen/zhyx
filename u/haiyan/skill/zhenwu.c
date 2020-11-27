// zhenwu.c ̫�������������а��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage, acter;

        if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
                return notify_fail("�㻹����ʹ�á������а����һ������\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������а��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("taiji-jian", 1) < 160)
                return notify_fail("���̫������������죬����ʹ�á������а����\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�����������������޷�ʹ�á������а����\n");

        if (me->query_skill_mapped("sword") != "taiji-jian") 
                return notify_fail("��û�м���̫���������޷�ʹ�á������а����\n");

        msg = HIY "$N" HIY "ƽƽ�ӳ�һ������ɨ$n" HIY "��\n" NOR;

        me->add("neili", -50);

        dp = (target->query_skill("force", 1) +  
             target->query_skill("parry", 1) + 
             target->query_skill("martial-cognize", 1)) / 3; 

        if (me->query("character") == "��������" || me->query("character") == "������") 
             acter = 3; 
        else 
             acter = 4; 

        ap = (me->query_skill("taiji-shengong", 1) + 
             me->query_skill("taiji-jian", 1) + 
             me->query_skill("martial-cognize", 1) +  
             me->query_skill("taoism", 1)) / acter;  

        if (target->is_bad()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIY "���$p" HIY "û�а����������ϣ���"
                                           "��Ӧ��һ�У�ȴ��$P" HIY "���ƺ�Ȼһ��"
                                           "��\n������ǧ���������������߷緶��\n"
                                           HIR "$p" HIR "����ʧ�룬���ڵ�������$P"
                                           HIR "��һ������Ҫ������Ѫ�������Ҳ��̶ã�\n" NOR);
                target->receive_damage("jing", damage / 3, me);
                target->receive_wound("jing", damage / 6, me);
                me->start_busy(2);
        } else
        {
                msg += HIG "����$p" HIG "������$P" HIG "����ͼ����"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

