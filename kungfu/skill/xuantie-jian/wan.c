// Created by kasumi 
#include <ansi.h>
#include <combat.h>
#define WAN "��" HIY "��������" NOR "��"
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage,attack_time,i,lvl1,lvl2;
        int ap, dp, as,ds;
        string wp, msg,msg1,parry_str;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(WAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" WAN "��\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("����ڹ���򲻹�������ʩչ" WAN "��\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 300)
                return notify_fail("�����������������죬����ʩչ" WAN "��\n");

        if ((int)weapon->query_weight() < 20000)
                return notify_fail("�����е�" + wp + "��������������ʩչ" WAN "��\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("�����ڵ��������㣬����ʩչ" WAN "��\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ" WAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	as=me->query("max_neili");
	ds=target->query("max_neili");
	parry_str=target->query_skill_mapped("parry");

			
	if (as/3 + random(as) > ds && random(2) == 1)
	{                                                                                                 
		call_out("kill_him", random(2)+1, me, target);                                             
		me->add("neili", -500);                                                                   
		msg = YEL "$N" YEL "��Ȼ���������еĹ��ƣ���Ŀ��󳷻أ��ƺ���ɱ����һ����ʧ�ˣ�\n" NOR;  
		msg += RED "Ȼ����������ȴ��$N���ɳ���$N��ɫҲԽ��Խ�죡\n"NOR;                          
		message_combatd(msg, me ,target);                                                        
		return 1;                                                                                  
        }
     else
	{
		ap = me->query_skill("xuantie-jian",1)+ me->query_str()*5;                                          
		dp = target->query_skill("parry",1) + target->query_dex()*4;   
		
		msg = HIC "$N" HIC"���쳤Х������" + wp + HIC"��ͷ���Եı�$n"HIC"��ȥ����ʱ����������������";                                                                    
		msg += HIC "����"HIW"������������"HIC"������"HIG"�������ε���"HIC"����$n"HIC"���ž������У�\n" NOR;
		message_sort(msg, me, target);
		
		
		lvl1 = (int) me->query_skill("surge-force",1)/100;
		lvl2 = (int) me->query_skill("yunv-xinjing",1)/100;
		if (lvl1>lvl2)
		 lvl2=lvl1;
		attack_time = 3 + random(lvl2);
           if (attack_time > 6)
              attack_time = 6;		 
                
		for (i = 0; i < attack_time; i++)
		{
		   
		   
		     msg1=HIR"                       $N��ȵ�����"+chinese_number(i+1)+HIR"����\n\n"NOR;
		   
		  
		 if ((ap*2/3+random(ap))>dp)
		   	{
		   target->map_skill("parry", 0);
		   target->add_temp("apply/parry", target->query_skill("parry",1));
		    
		   damage = me->query_skill("sword");
		   damage = damage + random(damage/2);
		   msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
		                           HIR "$n" HIR "���һ����ֻ����$N"HIR"�������糱ˮ��ӿ������ǰ�����������ڰ��ѱ档\n"  NOR);	
		   message_combatd(msg1, me, target);
		   target->add_temp("apply/parry", - target->query_skill("parry",1));
		   target->map_skill("parry", parry_str);
		  }
		  else
		  {
		  	msg1+=HIR"$n��֧�ҵ������ڱܿ�������\n" NOR;
        message_combatd(msg1, me, target);
		  	
		  }
		   
		}
		
		me->start_busy(3 + random(5));
		return 1;
	}		
}       

void kill_him(object me, object target)                                                                    
{
        string msg;
        if(me->is_fighting() && target->is_fighting() && living(me) && living(target)
	&& environment(me) == environment(target))
        {
         msg = HIR "������$n����£����ʱ$n��������һƬ��ˮ��Ľ����С�\n"                                
         "����ȫ��������ˮ�����$n����$n��ͷʱһ�ж��Ѿ�̫��˲�䱻��û�ˡ�\n" ;                        
         msg +=  HIR"���˹���$N��ɫ�ѻָ�ƽ����$nҲ�����˵��ϡ�����\n" NOR;                              

        message_combatd(msg, me, target);                                                                  
        target->unconcious();                                                                      
        }                                                                                                  
        me->start_busy(3);                                                                                 
        return;                                                                                           
}