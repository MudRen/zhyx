/* ����������ϼ�񹦶��˵��˽��ϣ�����һ������ͷֱ���������б������������ȺȦ 
ת�������������������������ӽ���Ծ��������Ⱥ�������ã����������ģ���һ������ 
�켫������屳�����۾����������Զ�ܡ�����"��"��һ���������˳������������ 
�ڰ�գ������޴���������ǰԾ���ؽ�����Ҳ�Ѳ�����ȴ��������ͦ����������ǰ������ 
��ľ��֮�ϣ���һ���������ӱ���Ծ����ľ��֮���۵�һ���죬����Ⱥ��������ľ���� 
�������ͣ������ھ���ע����������������������������������಻�����硣 
    �����ֶ�"��"��һ������һ���л��������г�����ϲ�á���ο����֮̾�飬������ 
�˶�����Ϊ����延ϲ�����������һ�¶������֮��������������Ⱥ����û���������� 
��Ⱥʩչƽ��������������������Ȼ�κβ�������壬���������˵Ľл������Ƕ���ͬ�� 
�Է������´��ǰ�ŭ����"�����������ɽ�"�ǻ�ɽ�ɽ��ڵľ����������ڵ���ԭ����֪ 
�����������ԲУ����ڵ������Դ˽���ɱ�˺ü������ں��֡������ڵ��ӽ����ڵĵ����� 
¾��������û�ɽ������֮�����ں�����ϸ��������ʽ����"�����������ɽ�"������ 
�������ն�ʱ����ʽ����������������������£�����֮ʱ�����˾�˵�����н������� 
ħ�������󽣷����ȴ���˱���"����Ԧ��"�Ĳ��������������˵��Ư��������ȴ 
�޲������*/
//Cracked by Kafei
//duoming.c �����������ɽ� 
#include <combat.h>
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string *limbs =
({
	"ͷ��", "����", "�ؿ�", "����", "���", "�Ҽ�", "���",
	"�ұ�", "����", "����", "����", "����", "����", "С��",
	"����", "����", "����", "���", "�ҽ�", "���", "�Ҷ�"
});
void chkpfm(object me, object target, int amount);
void remove_effect(object me, object target, int amount);
int perform(object me, object target)
{
	object weapon, weapon1;
	int lvl1, lvl2, amount;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�����������ɽ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (userp(me) && ! me->query("can_perform/huashan-sword/duoming"))
                return notify_fail("��δ������ָ�㣬��û��ѧ�����������\n");

	weapon = me->query_temp("weapon");
        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽������ʹ�ö����������ɽ���\n");

        if(me->query_skill_mapped("sword") != "huashan-sword") 
                return notify_fail("�㲢δʹ�û�ɽ����������ʹ�ö����������ɽ���\n");

	if (!living(target))
		return notify_fail("���Ѿ��ε��ˣ�������ʹ����˾����˰ɣ�\n");

	if (time() - target->query_temp("sxj-t") < 30)
		return notify_fail("���Ѿ���Ӧ����Ľ��У�������˵�Ѿ���Ч�ˣ�\n");

	if( me->query_skill_mapped("force") != "zixia-shengong" )
		return notify_fail("�����õĲ�����ϼ�����޷�ʩչ�����������ɽ���\n");

	if( (lvl1=me->query_skill("zixia-shengong", 1)) < 150 )
		return notify_fail("�����ϼ�����δ�����޷�ʩչ�����������ɽ���\n");

	if( (lvl2=me->query_skill("sword")) < 200 )
		return notify_fail("�㻪ɽ������Ϊ���㣬������ʹ�ö����������ɽ���\n");

	if( (lvl2 - lvl1) < lvl2 / 4 && lvl1 < 200)
		return notify_fail("�����������ɽ���Ҫ����տ�Ľ�����\n");

	amount = (lvl1+lvl2) / 5;

	if ( amount < 60 ) amount = 60;
	if ( amount > 200 ) amount = 200;

	if( me->query("neili") <= amount*10 )
		return notify_fail("�����������ʹ�ö����������ɽ���\n");
	if( me->query("jingli") <= amount*3 )
		return notify_fail("��ľ�������ʹ�ö����������ɽ���\n");

	if(!me->query_temp("sanxianjian"))
		message_vision(MAG "\nͻȻ��$N��һ����������������ʢ����ϼ��ʩչ������"NOR+
			weapon->name()+MAG"ĩ������������â������ɽ�������ӵ����쾡�¡�\n\n", me, target);

        message_vision(HIR "\n$N"+HIR+"�ĵ��ھ�����������"+NOR+weapon->name()+HIR+
		"�ϣ�����ɱ�ţ�һ����$n"+HIR+"��ͷֱ������\n\n" NOR, me, target);
	chkpfm(me, target, amount);

        message_vision(HIW "\n$N"+HIW+"һ�����У��������������ʯ���Ȧת"NOR+weapon->name()+
		HIW"����$n"+HIW+"������������\n\n" NOR, me, target);
	chkpfm(me, target, amount);
	me->set_temp("sxj-c" , 3);

        message_vision(HIY "\n$N"+HIY+"����������"NOR+weapon->name()+HIY"���ã�����$n"+HIY+
		"���ģ���һ�����м��죬$n�������۾����������Զ�ܣ���\n\n" NOR, me, target);
	chkpfm(me, target, amount);

	if((int)target->query("eff_qi") * 100 /(int)target->query("max_qi") <= 20
	 &&(int)target->query("qi") * 100 /(int)target->query("max_qi") <= 5
	 && me->query_temp("sxj-c") == 3)
	{
		message_vision(HIR "\n$N"+HIR+"�����ھ���ע������ǿ��֮����"+NOR+weapon->name()+HIR+"���������������͸��$n"+HIR+"�ؿ����磡��\n\n" NOR, me, target);
		target->receive_damage("qi",1,me);
		target->die();
	}
	if(!me->query_temp("sanxianjian")){
		me->add_temp("apply/damage", amount);
		me->add_temp("apply/attack", amount);
		me->add_temp("apply/sword", amount/3);
		me->set_temp("sanxianjian",1);
	        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, amount:), amount/5);
	}
        if (objectp(target) && living(target)) target->start_busy(1+random(2));
        me->start_busy(2+random(2));
	return 1;
}
void chkpfm(object me, object target, int amount)
{
	object weapon2 = target->query_temp("weapon");
        string attack_skill, dodge_skill, parry_skill, result, msg = "";
        int ap, dp, pp, damage, level;

        if( !me->is_fighting(target) || !living(target) ) 
                return;

        level = me->qeruy_skill("huashan-sword",1);
        damage = amount + random(level)/2 + me->query("jiali");
        damage += random(damage);
	ap = COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK);
	if( ap < 1) ap = 1;

	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
	if( target->is_busy() ) dp /= 3;
	if( dp < 1 ) dp = 1;
	if( random(ap + dp) < dp )
	{
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg();
	}
	else
	{
		pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
		if( target->is_busy() ) pp /= 2;
		if( pp < 1 ) pp = 1;

		if( random(ap + pp) < pp )
		{
			parry_skill = target->query_skill_mapped("parry");
			if( !parry_skill || !SKILL_D(parry_skill)->parry_available()) 
				parry_skill = "parry";
			msg += SKILL_D(parry_skill)->query_parry_msg(weapon2, target);
                        me->add("neili",-50);
		}
		else 
		{
			target->receive_damage("qi", damage*2, me);
			target->receive_wound("qi", damage, me);
			if (me->query_temp("sxj-c") == 3)
				result = COMBAT_D->damage_msg(damage, "����");
			else result = COMBAT_D->damage_msg(damage, "����");
			msg += result;
			result = COMBAT_D->status_msg((int)target->query("qi") * 100 /
				(int)target->query("max_qi"));
			msg += "( $n"+result+" )\n";
                        me->add("neili",-damage/3);
		}
	}
	result = limbs[random(sizeof(limbs))];
	msg = replace_string( msg, "$l", result );
	msg = replace_string( msg, "$w", (me->query_temp("weapon"))->name());
	message_vision(msg, me, target);
	return;
}

void remove_effect(object me, object target, int amount)
{
        if (!me) return;
	me->delete_temp("sanxianjian");
        if ( me->is_fighting() && objectp(target) && living(target))
	{
		message_vision(HIY "\n$n��������Ӧ��$P�����������ɽ��Ľ��硣\n" NOR, me, target);
		target->set_temp("sxj-t",time());
	}
	else message_vision(HIY "\n$N�ջ��ھ�,���лָ���ƽ����\n" NOR, me);
	me->add_temp("apply/damage", -amount);
	me->add_temp("apply/attack", -amount);
	me->add_temp("apply/sword", -amount/3);
}
