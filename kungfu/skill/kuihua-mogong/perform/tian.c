// wu.c �޷�����
// �������߿��֣������ý������붼����

#include <ansi.h>

inherit F_SSERVER;

#define WU "��" HIC "�޷�����" NOR "��"
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i;
 
        if (userp(me) && ! me->query("can_perform/kuihua-mogong/tian"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail(WU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query("neili") < 500)
		return notify_fail("��������������޷�ʩչ" WU "��\n");

	if ((lvl = me->query_skill("kuihua-mogong", 1)) < 250)
		return notify_fail("��Ŀ���ħ����򲻹����޷�ʩչ" WU "��\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("�㻹û�м�������ħ��Ϊ�ڹ����޷�ʩչ" WU "��\n");  

        if ((int)me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ���㣬����ʩչ" WU "��\n");

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin")
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ" WU "��\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ" WU "��\n");
        }

        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" WU "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" WU "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	      msg = HIR "$N" HIR "Ĭ�˿���ħ�������α������ޱȣ������Ӳ�ͬ�ķ�λ��$n"
              HIR "�������У�\n" NOR;
        
         msg += HIR "$n" HIR "ֻ������ǰһ�����������ܶ���$N"
                       HIR "����Ӱ�����ɰ������⣬�������ˡ�\n" NOR;
         message_combatd(msg, me, target);
                       
         i = 9 + random(4);
         count = me->query_skill("kuihua-mogong", 1);
         me->add_temp("apply/attack", count);  
         me->add_temp("apply/damage",count/4);    
 	       me->add("neili", -i * 50);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2)==1 && ! target->is_busy())
                        target->start_busy(1);
               /* msg = HIM"$N" HIM "�������ħ��������Ȼ�ӿ죬��Х����" HIM"$n" HIM "�������һȦ��\n"NOR;             
                        message_combatd(msg, me, target);  */ 
        	if (weapon)
        	COMBAT_D->do_attack(me, target, weapon, 0);
        	else
        	COMBAT_D->do_attack(me, target, 0, 0);	
        }

        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count/4);
      	me->start_busy(1 + random(4));
	return 1;
}
