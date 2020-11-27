// updated by Kasumi
     
#include <ansi.h>

inherit F_SSERVER; 
       
int perform(object me, object target) 
{ 
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail( "��ŭ�����Ρ�ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail( "��ŭ�����Ρ�ֻ�ܿ���ʹ�á�\n");

		 if (me->query("family/family_name") != "��Ĺ��")     
                return notify_fail("ֻ�й�Ĺ���Ӳ����á�ŭ�����Ρ���\n");     

        if( me->query_skill_mapped("force") != "surge-force" )
                return notify_fail("�������ڹ��Ĳ���ŭ�����Σ�ʹ������ŭ�����Ρ���\n");

        if( (int)me->query_skill("surge-force",1) < 400 )
                return notify_fail("���ڹ���Ϊ̫��������á�ŭ�����Ρ���\n");

        if( me->query_skill("sad-strike",1) < 400 )
                return notify_fail("����Ȼ��������Ϊ̫��������á�ŭ�����Ρ���\n");
	
        if( (string)me->query_skill_mapped("unarmed") != "sad-strike")
		return notify_fail("�㲢û�м�����Ȼ��������Ϊ�Ʒ���\n");

        if( (string)me->query_skill_prepared("unarmed") != "sad-strike")
		return notify_fail("�㲢û��׼����Ȼ�����ơ�\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if( me->query("neili") < 1200 )
                return notify_fail("�����������ʹ�á�ŭ�����Ρ���\n");

        ap = me->query_skill("force") + me->query_skill("unarmed") + me->query_skill("dodge") + me->query_skill("parry") ;
	dp = target->query_skill("force") + me->query_skill("unarmed") + target->query_skill("dodge") + target->query_skill("parry");

     msg = HIW"\n$N���Ʒ��������ų�ӿ֮�����Ʒ�ĵ��������п�ӿ���������������������ں��������ľ�����\n"NOR;
	
	 if (ap + random(ap) > dp)
	{
		msg += HIR"$n�����ܵÿ��������Ѿ���$N���Ʒ�ӡ���ؿڣ�һ����Ѫ���������\n"NOR;

		target->receive_wound("qi",ap+random(ap),me);
		str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n" ;		
         if (! target->is_busy()) 
			target->start_busy(1);
	} else
	{
		msg +=CYN"$n��״������̾͵�һ���������Ȼ�����ѿ��Լ�����������ܿ���$N��һ�ơ�\n"NOR;
	}
      message_combatd(msg, me, target);


    msg = HIW"\n$N���Ʒ�ﵽ����֮ʱ�����š��겻���ᡱ����������ʩ������������ʧ�����������С�\n"NOR;
	
	if (ap + random(ap) > dp)
	{

		msg +=HIR"$n����δ����������֮�ʣ��������һ�����ҵ������������������$N�Ʒ��ش���\n"NOR;
		target->receive_wound("qi",ap+random(ap),me);
		str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n" ;		
		
             if (! target->is_busy()) 
			target->start_busy(1);
	} else
	{
		msg += CYN"$n�˲��÷���������������ɣ����ո�$N���Ʒ�ɨ����΢΢���죬��������ܿ���$N�����ơ�\n"NOR;
	}
	message_combatd(msg, me, target);
	
         msg = HIW "\n����$N�������һ�С���ʬ���⡱��������߳�һ�š�\n"NOR;

	if (ap + random(ap) > dp)
	{
		msg += HIR"$n�ۿ�������������һ�ţ���Ȼ�����˵ֿ�������������$N�������ϣ����ݽ��飬��ĿѪɫ������\n"NOR;
		target->receive_wound("qi",ap*3/2+random(ap),me);
		str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n" ;		
		
                if (! target->is_busy()) 
			target->start_busy(1);
	} else
	{
		msg += CYN"$n˫���أ�������𣬴�$N��ͷ���ӹ������¾�����Х������������֮���գ�\n"NOR;
	}
	message_combatd(msg, me, target);

        me->add("neili",-1000);
	    me->start_busy(2+random(3));

        return 1;
}        
