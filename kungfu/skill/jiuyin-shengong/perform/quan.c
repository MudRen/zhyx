// quan �����޼���
// created by kasumi
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define QUAN "��" HIW "�����޼���" NOR "��"
 
int perform(object me, object target)
{
	string msg,str;
	int ap, dp;
        int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail(QUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_skill("jiuyin-shengong", 1) < 220)
		return notify_fail("��ľ����񹦻�������죬����ʹ��" QUAN "��\n");

	        if (me->query("neili") < 1500)
                return notify_fail("�����������������ʹ��" QUAN "��\n");

        if (me->query_temp("weapon"))
                return notify_fail("����ֻ�ܿ���ʩչ��\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-shengong"
           && me->query_skill_prepared("cuff") != "jiuyin-shengong")
                return notify_fail("��û��׼��ʹ�þ����񹦣��޷�ʩչ" QUAN "��\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "һ����ߣ�������ȭ��������ʽ�ۻ룬��ߪ������\n" NOR;
 
	ap = me->query_skill("jiuyin-shengong", 1) + me->query_skill("martial-cognize", 1) + me->query_skill("force", 1);
        dp = target->query_skill("jiuyin-shengong", 1) + target->query_skill("martial-cognize", 1) + target->query_skill("parry", 1);

        
        me->add("neili", -100);
		damage = me->query_skill("force") + me->query_skill("unarmed") + me->query_str() * 25;

        if (ap * 3/4 + random(ap) > dp)
        {
			if (me->query_skill("jiuyin-shengong", 1) > 500)
			{
			   damage = damage + random(damage/2);
			   target->receive_wound("qi", damage, me);
	           str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	           msg += HIR "$n" HIR "��æ�񵲣�������һȭ�����ε�֮�أ�����ֵ���ס��ֻ�������Ѫ���ߣ��������ɣ�\n" NOR;
			   msg += "($n"+str+")\n";
			   me->add("neili",-500); 
				if (me->query("reborn")) {
					msg += HIC "$N" HIC "�ٴ���ߣ�������ȭ��������ʽ�ۻ룬��ߪ������\n" NOR;
					damage = damage + random(damage);
					target->receive_wound("qi", damage, me);
					str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
					msg += HIR "$n" HIR "��æ�񵲣�������һȭ�����ε�֮�أ�����ֵ���ס��ֻ�������Ѫ���ߣ��������ɣ�\n" NOR;
					msg += "($n"+str+")\n";
					me->add("neili",-500); 
					msg += HIC "$N" HIC "��������ߣ�˫ȭ��������ʽ�ۻ룬��ߪ������\n" NOR;
					damage = damage + random(damage);
					target->receive_wound("qi", damage, me);
					str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
					msg += HIR "$n" HIR "��æ�񵲣�������һȭ�����ε�֮�أ�����ֵ���ס��ֻ�������Ѫ���ߣ��������ɣ�\n" NOR;
					msg += "($n"+str+")\n";
					me->add("neili",-500); 
					me->start_busy(3);
				}
			}
			else
			{
        	me->add("neili",-100);            
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85 + random(15),
                                      HIR "$n" HIR "��æ�񵲣�������һȭ�����ε�֮�أ������"
                                          "����ס��ֻ�������Ѫ���ߣ�����������\n" NOR);
					me->start_busy(1);
			}
		
        } else
	      {
		            msg += HIG "ֻ��$n" HIG "���Ų�æ������һ���������$N" HIG "��һ����\n"NOR;
					me->start_busy(2);
	      }

	message_combatd(msg, me, target);
	return 1;
}
