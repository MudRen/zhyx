// Code of JHSH
// lianhuan.c �ѹ�ӥצ��������ӥץ
/// maco

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	int claw, lv, i, hit;
	string weapon, lzg_msg;

	if( !target ) target = offensive_target(me);
	
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�ѹ�ӥצ����צ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("lzg_effect") )
                return notify_fail("��ղ��Ѿ�ʹ�����ѹ�ӥצ������������һʱ��������������\n");

	if ( me->query_temp("weapon") )
                return notify_fail("�ѹ�ӥצ����������������ַ���ʩչ��\n");

	if( me->query_skill("force", 1) < 100 )
		return notify_fail("����ڹ����δ�����޷�ʩչ�ѹ�ӥצ������������\n");

	if( me->query_skill("claw",1) < 140 )
		return notify_fail("���צ����Ϊ���ޣ��޷�ʩչ�ѹ�ӥצ������������\n");

	if( me->query_skill("sougu",1) < 140 )
		return notify_fail("����ѹ�ӥצ������δ�����޷�ʩչ�ѹ�ӥצ������������\n");

	if( me->query("neili") <= 300 )
		return notify_fail("�������������ʹ���ѹ�ӥצ������������\n");

	if( me->query("jingli") <= 200 )
		return notify_fail("��ľ�������ʹ���ѹ�ӥצ������������\n");

	claw = me->query_skill("claw");
	lv = (int)me->query_skill("sougu",1);
	hit = (lv/100)*2;
	if(hit > 8) hit = 8;
	if(hit <4) hit = 4;
	
	me->add_temp("apply/attack", lv/5);
	me->add_temp("apply/damage", lv/5);

	lzg_msg = HIY"\n$NͻȻ����һ����������ϣ�˫�����������꣬";
	
	if(hit >= 4)lzg_msg += "����צʽ��������צʽ��������צʽ��������צʽ��";
	if(hit >= 6)lzg_msg += "������צʽ��������צʽ��";
	if(hit >= 8)lzg_msg += "����ǧצʽ��������צʽ��";
		
	lzg_msg += "��"+chinese_number(hit)+"ʽ����������������\n"NOR;

	message_vision(lzg_msg, me, target);
	me->set_temp("lzg_times",hit);
	me->set_temp("lzg_effect",1);
	me->add_temp("lzg_lianhuan", 3);
        for( i=0; i < hit; i++ )
        {
		me->add_temp("lzg_lianhuan", 1);
                COMBAT_D->do_attack(me, target, weapon);
        }

	me->add_temp("apply/attack", -lv/5);
	me->add_temp("apply/damage", -lv/5);

        message_vision(HIY"\n��"+chinese_number(hit)+"ʽ�����ķ�ӥץ���಻����������һ���е�"+chinese_number(hit)+"���仯һ�㣬����ޱȣ�\n"NOR, me);

	me->add("neili", -hit*20+20);
	me->add("jingli", -hit*5);
	me->start_busy(1+random(2));
	me->delete_temp("lzg_lianhuan");
	me->delete_temp("lzg_times");
        call_out("remove_effect", hit*2, me);
	return 1;
}


void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("lzg_effect");
        tell_object(me, YEL"\n��΢һ��Ϣ��ƽ����ʩչ�ѹ�ӥצ����ĵ����ڵ�������\n"NOR); 
}
