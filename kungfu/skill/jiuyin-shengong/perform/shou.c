// shou.c ������Ԫ��
// created by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define SHOU  "��" HIG "������Ԫ��" NOR "��"
 
int perform(object me, object target)
{
	string msg;
        int ap, dp;
        
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail(SHOU "ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("����ֻ�ܿ���ʩչ��\n");

	if (me->query_skill("jiuyin-shengong", 1) < 220)
		return notify_fail("��ľ����񹦻�������죬����ʹ��" SHOU "��\n");

	if (me->query("neili") < 500)
		return notify_fail("�������������\n");

        if (me->query_skill_prepared("hand") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" SHOU "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

       msg = HIY "$N" HIY "��������һ���³���һ��������ʽ���أ�������ı���$n"
              HIY "��ҪѨ��\n";

        ap = me->query_skill("jiuyin-shengong",1);
        dp = target->query_skill("parry",1);

       if (ap * 3 / 5 + random(ap) > dp) 
        { 
             msg +=  HIR "$n" HIR "ֻ�����У������ޱȣ�����Ī�⣬"
                         "����һ����ȴ��Ȼ�����һ������͸�Ƕ�����\n" NOR;
			 target->start_busy(random(ap / 30) + 2);
       me->add("neili", -100);
       target->set("neili", target->query("neili") / 2);
			 me->start_busy(1);
		}
		else
		{
			msg += HIC "$n" HIC "֪�����в��ƣ�С��Ӧ�ԣ�û��һ����\n" NOR;
			me->add("neili", -50);
		    me->start_busy(2);
		}
 
		message_combatd(msg, me, target);
        return 1;
}
        
