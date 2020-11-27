// Code of JHSH
///kungfu/skill/duanyun-bian/fengyun.c ���Ʊ�ɫ
// sdong 09/98

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	int str, dex, skill,power;
	string weapon;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("���Ʊ�ɫֻ�ܶ�ս���еĶ���ʹ�á�\n");


	if( me->query_skill_mapped("force") != "xiantian-gong" )
		 return notify_fail("�����õĲ����������칦��ʩչ�������Ʊ�ɫ��\n");

	if( me->query_skill("force") < 140 )
		return notify_fail("����������칦���δ�����޷�ʩչ���Ʊ�ɫ��\n");

	if( me->query_skill("whip") < 135 )
		return notify_fail("���Ʊ�ɫ��Ҫ��տ�Ķ��Ʊ޷�������Чʩչ��\n");

        if (!me->query_temp("weapon") || me->query_temp("weapon")->query("skill_type") != "whip")
                return notify_fail("�㲢û��װ������Ϊ������\n");
	str = me->query_str();
	power = random( me->query("neili") / 50 ) + me->query("force")/2;
	if(power<150) power=150;
	if(power>480) power=480;

	if( me->query("neili") <= 200 + power*2 )
		return notify_fail("�����������ʹ�÷��Ʊ�ɫ��\n");

	message_vision(HIW "$N�����������͵�һ��"NOR+"$n"+HIW"�����ޱ߷����������գ�һ��"NOR+HIM"�"NOR+HIW"���������Ӱ����ǵص������Ϯ����\n\n" NOR, me, me->query_temp("weapon"));

	me->add_temp("apply/attack",power/2);
	me->add_temp("apply/damage",power/5);
	target->add_temp("apply/armor",-power/2);
	target->add_temp("apply/dodge",-power);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->add_temp("apply/attack",-power/2);
	me->add_temp("apply/damage",-power/5);
	target->add_temp("apply/armor",power/2);
	target->add_temp("apply/dodge",power);

	me->add("neili", -power*2);
	me->add("jingli", -power/2);
	me->start_busy( 2+random(2));

	return 1;
}


