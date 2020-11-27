// Code of JHSH
///kungfu/skill/chongyang-shenzhang/lianhuan.c ��������

/*
��־ƽ��ƽ�̣�����������ͬʱ���Ⱥ�ɨ����������ȫ�����еġ������������С���־���������ţ�
�ӽ���������־ƽ�������֣������Է���ȥ���������١���һ����˫�������

������⼸��������ã��ѷǼ�֮��֪������������ȫ���亹���ۼ���־�����ڰ�գ�һ�����飬һ
����ʵ������������Ҫ��������۹Ƕϡ���֪��־������������Σ���쳣֮�ʺ�Ȼ���з�������Ѱ
�ɣ��������ɵ�����������
*/


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill;
	string weapon;
	int damage;
	string *limb, type, result, str;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");


	if( objectp(me->query_temp("weapon")) )
		return notify_fail("������������ֲ���ʩչ��\n");

	if( me->query_skill_mapped("strike") != "chongyang-shenzhang" )
		return notify_fail("�����õĲ����������ƣ�����ʩչ�������У�\n");

	if( me->query_skill_prepared("strike") != "chongyang-shenzhang" )
		return notify_fail("�������Ĳ����������ƣ�����ʩչ�������У�\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("�����õĲ����������칦��ʩչ�����������У�\n");

	if( me->query_skill("force") < 120 )
		return notify_fail("����������칦���δ�����޷�ʩչ�������У�\n");

	if( me->query_skill("strike") < 120 )
		return notify_fail("����������Ҫ��տ���������Ʒ�����Чʩչ��\n");

	if( me->query("neili") <= 200 )
		return notify_fail("�����������ʹ���������У�\n");

	message_vision(HIY "$Nŭ��һ�����վ�ȫ����ͻȻ����㹥��ָ���ơ����������У�\n\n" NOR, me, target);

	skill = me->query_skill("strike")/2 + me->query_skill("strike") / 8;
	if(skill>300)skill=300;
	me->add_temp("apply/attack",skill);
/*
        if(me->query_temp("apply/attack")> 400){
		me->set_temp("apply/attack",400);
	}
*/

	if( me->query_skill_prepared("strike") == "chongyang-shenzhang" ) {
		me->set_temp("restore", 1);
		me->prepare_skill("strike");
	}

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	if( me->query_temp("restore") ) me->prepare_skill("strike", "chongyang-shenzhang");

	if( me->query_skill_prepared("finger") == "zhongnan-zhi" ) {
		me->set_temp("restore", 1);
		me->prepare_skill("finger");
	}

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	if( me->query_temp("restore") ) me->prepare_skill("finger", "zhongnan-zhi");
	me->add_temp("apply/attack",-skill);

	message_vision( HIY "\n������$NͻȻ�ڿշ���ʹ��һ��ԧ�������ȣ����ȷ�۵糸��������$n\n" NOR,me,target);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3)
	{
		if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) )
		{
			message_vision(HIR"ֻ��$Nһ���ҽУ����������������Ŀڡ�����$nһ������ͻȻƽƽ�ɳ����ڵ�һ�죬���������������֮�⣬ֱͦͦ�����ڵ��£���Ҳ������\n\n"NOR, target,target );
                        damage = (int)target->query("eff_qi");
                        target->receive_wound("qi", (damage>0?damage:-damage), me);
                        damage = (int)target->query("qi");
                        target->receive_wound("qi", (damage>0?damage+1:1-damage), me);
			me->add("neili", -me->query("jiali"));
		}
		else
		{
			damage = random((int)me->query_skill("strike")+me->query("jiali")) ;
			if(damage > 1500) damage = 1500;
			if(damage < 300) damage = 300;
			me->add("neili", -me->query("jiali"));

			target->receive_damage("qi", damage,  me);
			target->receive_wound("qi", (int)me->query_skill("strike"), me);

			limb = target->query("limbs");
			type = "����";
			message_vision("ֻ��$Nһ���ҽУ���������������$P"+limb[random(sizeof(limb))]+"�������$P��ˤ�˸���ͷ��\n",target);

			str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
			message_vision("($N"+str+")\n", target);
		}
		me->start_busy(1+random(2));
	}
	else if( ( random( target->query_skill("dodge") ) >  me->query_skill("strike")*2/3) && random(5) == 1 )
	{
		message_vision(HIR"$N�;��þ�����������֪�����æ���������$n���˸��գ��װ��Լ����ص���һ�ӡ�\n\n"NOR, target,me );
		me->receive_wound("qi", 30+random(50),  me);
		me->start_busy(2+random(2));
		str = COMBAT_D->status_msg((int)me->query("qi") * 100 /(int)me->query("max_qi"));
		message_vision("($N"+str+")\n", me);
	}
	else
	{
		message_vision( "$N�ۼ���һ���������ͣ�����˫��һ�㣬Ծ���ĳߣ��㿪��$n��һ�У�����Ҳ����һ���亹��\n\n" NOR,  target,me);
		me->start_busy(2);
	}

	me->add("neili", -random(me->query_skill("strike")/4) -100 );
	me->start_busy( 2+random(2) );

	return 1;
}


