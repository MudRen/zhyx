// lei.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
	      string msg,str;
        int level,damage,n;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail("�������ֻ����ս���жԶ���ʹ�á�\n");

	if (me->query_skill("never-defeated", 1) < 220)
		return notify_fail("��Ĳ����񹦻�������죬����ʹ�����������\n");

        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("������ֱֳ��в���ʩչ���������\n");

	if (me->query("neili") < 500)
		return notify_fail("�������������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���һ�������е�" + weapon->name() +
              HIC "�������£����Ƽ򵥣���Ȼ��ס��$n"
              HIC "���е���·��\n" NOR;
        msg += HIR "$n" HIR"�޷���͸���������Һ�����ɽ�����Ѫ�ڿ����лص�......\n"NOR;

        level = me->query_skill("never-defeated", 1);
        if (level < 1000)  {target->receive_wound("qi", target->query("qi")/2000,me);}
      else if (level < 1200) {target->receive_wound("qi", target->query("qi")/1500,me);}
        else {target->receive_wound("qi", target->query("qi")/1200,me);}                   
        
        
	      str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	      msg += "($n"+str+")\n";
	      me->add("neili", -300);
	      me->start_busy(4 + random(4));
        message_combatd(msg, me, target);

	return 1;
}
