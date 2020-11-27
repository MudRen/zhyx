#include <ansi.h>
#include <combat.h>

#define ZHENWU "��" HIY "�����а" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);
string final2(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHENWU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHENWU "��\n");

        if ((int)me->query_skill("taiji-jian", 1) < 180)
                return notify_fail("���̫������������죬����ʩչ" ZHENWU "��\n");

        if (me->query("neili") < 200)
                return notify_fail("��������������������ʩչ" ZHENWU "��\n");

        if (me->query_skill_mapped("sword") != "taiji-jian") 
                return notify_fail("��û�м���̫������������ʩչ" ZHENWU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        
msg = HIG "$N" HIG "��ǰһ����ƽƽ�ӳ�һ������ɨ$n" HIG "��ȥ����"
              "�ް�㻨�ɿ��ԡ�\n" NOR;
        
        ap = me->query_skill("sword")+(int)me->query_skill("taoism", 1)*2/3;
        dp = target->query_skill("parry");
        if (target->is_bad()) ap += ap / 8;
		damage = ap*2 + random(ap*2);

		if (me->query_skill_mapped("force") == "taiji-shengong")
		{
			me->add("neili", -100);
			damage+=(int)me->query_skill("taiji-shengong", 1);
		}
		else
		{
			me->add("neili", -50);			
		}

        me->start_busy(3);
        if (ap * 2 / 3 + random(ap) > dp)
        {
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                           (: final, me, target, damage :));
        } else
        { msg += HIC "����$n" HIC "��͸$P" HIC "�к����ɱ�ţ���"
                      "����㣬ȫ��Ӧ�����硣\n" NOR; 
                      
        	if (ap * 3 / 4 + random(ap) > dp)
             {msg += HIW "$N" HIW "�˺�һ�����ٳ�һ������ɨ$n" HIW "��ȥ����"
              "�ް�㻨�ɿ��ԡ�\n" NOR;
            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           (: final, me, target, damage :));
             } 
                 
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("qi", damage / 2, me);
        target->receive_wound("qi", damage / 3, me);
        return  HIY "���$n" HIY "ȴ˿��δ�����з����������Ӧ��һ�У�ȴ��$N"
                HIY "����\n��Ȼһ�䣬������ǧ���������������߷緶��\n" NOR +
                HIR "$n" HIR "��ʱ����ʧ�룬��$P" HIR "��һ������Ҫ������Ѫ����"
                "���Ҳ��̶ã�\n" NOR;
}
