// qingfu.c ΢�������
 
#include <ansi.h>
#include <combat.h>

#define QINGFU "��" HIG "΢�������" NOR "��"
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
       object weapon;
	string msg;
	int ap, dp;
       int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }
       weapon = me->query_temp("weapon");

        if ( ! me->query("can_perform/xuannv-jian/qingfu"))
                 return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");   

	if (! target || ! me->is_fighting(target))
		return notify_fail(QINGFU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("xuannv-jian", 1) < 180)
		return notify_fail("�����Ů������������죬����ʹ��" QINGFU "��\n"); 

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
		return notify_fail("�������õĲ��ǽ�����ôʩչ" QINGFU "��\n");                 

        if (weapon && me->query_skill_mapped("sword") != "xuannv-jian")
                return notify_fail("��û��׼��ʹ����Ů����������ʩչ" QINGFU "��\n");

        if (me->query("neili") < 300)
                return notify_fail("�����������������ʹ��" QINGFU "��\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG"$N�ڶ������������ƺ�����ʹ��������һ��΢���������$n��硣\n" NOR;
 
	ap = me->query_skill("xuannv-jian", 1) * 2 + me->query("per") * 20 + me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry",1) + target->query("per") * 20 + target->query_skill("martial-cognize", 1);

        me->start_busy(1);
        me->add("neili", -100);

        if (ap * 4/5 + random(ap) > dp)
        {
        	 me->add("neili",-50);
           damage = ap * 2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70+random(30),
                                           HIR "$n" HIR "��Ϊ����ƽ�����棬���ڷ����������$N"
                                           HIR "һ���������ţ���Ѫ����һ�أ�\n" NOR);
		
        } else
	      {
		       msg += HIC "Ȼ��$n" HIC "��Ϊ���л�������С��Ӧ������$N" HIC
                       "����һһ���⡣\n" NOR;
	      }

	message_combatd(msg, me, target);
	return 1;
}
