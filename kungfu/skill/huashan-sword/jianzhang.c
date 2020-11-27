// Code of ShenZhou
//jianzhang.c ���������� 

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	string weapon;
	object weapon1;
	int    lvl1, lvl2, amount;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon1 = me->query_temp("weapon");
        if( !objectp(weapon1) || weapon1->query("skill_type") != "sword" )
                return notify_fail("�������޽������ʹ�ý�����������\n");

        if(me->query_skill_mapped("sword") != "huashan-sword") 
                return notify_fail("�㲢δʹ�û�ɽ����������ʹ��������������\n");

        if( me->query_temp("secondary_weapon"))
                return notify_fail("�������Ŷ̱�,û�ж����������ʹ����Ԫ�ơ�\n");

	if( me->query_skill_mapped("strike") != "hunyuan-zhang" )
		return notify_fail("�����õĲ��ǻ�Ԫ�ƣ������뻪ɽ�������ʩչ������������\n");

	if( me->query_skill_prepared("strike") != "hunyuan-zhang" )
                return notify_fail("�������Ĳ��ǻ�Ԫ�ƣ������뻪ɽ�������ʩչ������������\n");

	if( me->query_skill_mapped("force") != "zixia-shengong" )
		return notify_fail("�����õĲ�����ϼ�񹦣��޷�ʩչ������������\n");

	if( me->query_skill("zixia-shengong", 1) < 60 )
		return notify_fail("�����ϼ�񹦻��δ�����޷�ʩչ������������\n");

	if( (lvl1=me->query_skill("strike")) < 100 )
		return notify_fail("������������Ҫ��տ�Ļ�Ԫ����ϣ�������Чʩչ��\n");

	if( (lvl2=me->query_skill("sword")) < 100 )
		return notify_fail("�㻪ɽ������Ϊ���㣬������ʹ�ý�����������\n");

	amount = (lvl1+lvl2) / 15;

	if ( amount < 30 ) amount = 30;
	if ( amount > 100 ) amount = 100;

	if( me->query("neili") < amount*3 )
		return notify_fail("�������������㣬�޷�ʹ�ý�����������\n");

	if( me->query("neili") <= amount*4 )
		return notify_fail("�����������ʹ�ý�����������\n");
        if (me->queyr("jingli") < 0)
		return notify_fail("��ľ�������ʹ�ý�����������\n");

	if( me->query_skill_prepared("cuff") == "pishi-poyu" ) {
		me->set_temp("restore", 1);
		me->prepare_skill("cuff");
	}

	weapon = me->query_temp("weapon");

	me->add_temp("apply/damage", amount);
	me->add_temp("apply/attack", amount*2);
	me->add_temp("apply/dodge", amount);
	me->set_temp("kuangfeng_kuaijian",1);

	message_vision(HIR "\nͻȻ��$N���ε�����˲��ƽ�$n������������������$n���������������ƣ�\n\n" NOR, me, target);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	weapon->unequip();
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	weapon->wield();
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	weapon->unequip();
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	weapon->wield();
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->start_busy(1+random(3));
	me->add_temp("apply/damage", -amount);
	me->add_temp("apply/attack", -amount*2);
	me->add_temp("apply/dodge", -amount);
	me->delete_temp("kuangfeng_kuaijian");
	me->add("neili", -amount*3);
	if( me->query_temp("restore") ) me->prepare_skill("cuff", "pishi-poyu");

	return 1;
}
