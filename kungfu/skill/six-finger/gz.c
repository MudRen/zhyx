#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg;
	int ap,dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

              if (me->query_skill_mapped("finger") != "six-finger") 
                      return notify_fail("��û�м��������񽣣��޷�ʩչ���������ڡ���\n"); 

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ���������ڣ�\n");
             
        if( (int)me->query_skill("six-finger", 1) < 200 )
             return notify_fail("��������񽣲�����죬����ʹ���������ڡ�\n");
              
        if( (int)me->query("max_neili", 1) < 8000 )
                return notify_fail("����������������񣬲���ʹ�������뷢��\n");
                        
        if( (int)me->query("neili", 1) < 1500 )
           return notify_fail("����������̫��������ʹ���������ڣ�\n");

              if (me->query_skill_prepared("finger") != "six-finger") 
                      return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ���������ڡ���\n"); 

        msg = HIY
"$Nʹ����������ǿ�������������ڡ����������˾Ŵ����죬������ӿ���ȣ�\n"+HIR"ɲʱ�����ɳ��ȸ��͵Ľ�����ָ�������������Ѹ�׼����໥��ײ��֮�ʣ�\n"+HIW"��Ȼ�㼯��һ��������ƥ�Ľ���������һ����ɫ����,����㼲����$n������\n"NOR,
             me->add("neili", -500);
	
	ap =  me->query_skill("force");
	ap += me->query_skill("finger");
	ap += me->query_str()*10;
	ap += random(ap/2);
	dp =  target->query_skill("force");
	dp += target->query_skill("parry");
	dp += target->query_dex()*10;
	dp += random(dp/2);
        ap += random(1+(int)me->query("jiali")/2);
        if (ap > dp || !living(target))
        {
                me->start_busy(2);
                target->start_busy(random(3));
                
                damage = (int)me->query_skill("force");
               
                damage = damage*3 + random(damage);
                damage += me->query("jiali")*2;
                damage += me->query("jianu")*(10+random(20));
                
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
	        me->add("neili", -damage/2 );
                
                if( damage < 20 ) msg += HIY"���$n�ܵ�$N�Ľ������У��ƺ�һ����\n"NOR;
                else if( damage < 40 ) msg += HIY"���$n��$N�Ľ������У����١���һ������������\n"NOR;
                else if( damage < 80 ) msg += 
RED"���$n��$N�Ľ������У��ؿ������ܵ�һ���ش�����������������\n"NOR;
                else msg += 
HIR"���$n��$N�Ľ������У�����[��]���³�һ����Ѫ�������絾����һ�����ɳ�������\n"NOR;

		if (!me->is_busy())
			me->start_busy(2 + random(2));
		target->start_busy(1 + random(2));               
        } else 
 
 
        {
                me->start_busy(5);
                msg += CYN"����$p������$P����ʽ������΢΢һ���Ѿ��ܿ���$P�ġ��������ڡ���\n"NOR;
        }
        message_vision(msg, me, target);

        return 1;
}


