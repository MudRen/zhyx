//by snowyu
//updated by lara 2001/12/07
//����������
/*
   ����������վ�������������������б����쬵�һ�����죬���һ֦������
�Ʒ���𣬸����������б��������һ֦����ȻϨ������������ƣ���Ϩ����
֦�����۹�ʼ����ǰ������ȴ��������ˮ������֮����
ľ���循�������⡭�����ǡ����������ơ���������ôҲ�᣿��
*/
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	string weapon;
	int strike, force, amount; 
	strike = me->query_skill("strike");
	force  = me->query_skill("force");
	amount = (strike+force)/4;
	
        if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	if ( me->query_temp("weapon") )
                return notify_fail("�������̱�����ַ���ʩչ��\n");

        if( me->query_temp("piaomiao") ) 
		return notify_fail(HIW "������ʹ������Ʈ�죡\n"); 
	
  	if( me->query_skill_mapped("strike") != "wuluo-zhang" )
                return notify_fail("�����ò�������������!");

	if( me->query_skill_prepared("strike") != "wuluo-zhang" )
                return notify_fail("��������������������!");
          
        if( me->query_skill_prepared("cuff") != "jinyu-quan" )
                return notify_fail("����������ͽ���ȭ���ʹ��!");

	if( me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail("�������ڹ��ķ�����,�޷�ʩչ�������̣�\n");

	if( me->query_skill("kurong-changong",1) < 120 &&
            me->query_skill("duanshi-xinfa",1) < 120)
		return notify_fail("����ڹ���Ϊ�������޷�ʩչ�������̣�\n");

	if( me->query_skill("wuluo-zhang",1) < 120 )
		return notify_fail("�����������ƹ����������޷�ʩչ�������̣�\n");
		
	if (me->query("dali/betrayer")>=1)
            //return notify_fail("�����ѳ�����������˼ʹ�ô����ѧ��\n");   
	
	if (!me->query("can_perform/wuluo-zhang/qingyan") )
	        return notify_fail("��δ��������ָ�㣬����ʹ���������̣���\n");
	   
	if( (int)me->query("max_neili") <1000)
	        return notify_fail("���������Ϊ���㣬�޷�ʩչ�������̣�\n");
	        
	if( me->query("neili") < 300 )
		return notify_fail("�����������ʹ���������̣�\n");

        if( me->query("jingli") < 200 )
                return notify_fail("��ľ�������ʹ���������̣�\n");
       
               

        message_vision(WHT "$NͻȻ������Խ�𣬺����������б���������������б����˲����$n��������,����ȴ��������ˮ������֮��!\n\n" NOR, me, target);

	amount = (amount + random(amount*4))/2; //���͹̶�ֵ����������

        if(amount > 600 ) amount =600;  
        if(amount < 100 ) amount =100;
        
	me->add_temp("apply/damage", amount/2); //����һ���˺�
	me->add_temp("apply/attack", amount/2); //����һ�빥��
	me->prepare_skill("cuff");
	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	
	me->prepare_skill("cuff" , "jinyu-quan");
	
        me->add("neili", - amount+random(80));
        me->add("jingli", -amount+random(40));

	me->start_busy(1 + random(2));

        me->add_temp("apply/damage", -amount/2);
	me->add_temp("apply/attack", -amount/2);

	return 1;
}
