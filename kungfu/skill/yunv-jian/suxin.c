// Code of JHSH
// suxing.c ���ľ�

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
	string msg;
	object weapon;
	int damage,ap,dp,married;
 
        if( me->query("gender") != "Ů��")
                return notify_fail("��Ů����ֻ����Ů���ã�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ľ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill_mapped("force") != "yunv-xinfa" )
		return notify_fail("�����õĲ�����Ů�ķ����޷�ʩչ���ľ���\n");

	if( me->query_skill("yunv-xinfa", 1) < 200 )
		return notify_fail("�����Ů�ķ����δ�����޷�ʩչ���ľ���\n");

	if( me->query_skill("yunv-jian", 1) < 200 )
		return notify_fail("�����Ů���Ľ������δ�����޷�ʩչ���ľ���\n");

	if( !(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õı������ԡ�\n");

	if( !stringp(me->query_skill_mapped("sword")) ||
	    me->query_skill_mapped("sword") != "yunv-jian")
		return notify_fail("����뼤����Ů���Ľ���Ϊ�������ܹ�ʹ�����ľ���\n");

	if( me->query("neili") < 1000 )
		return notify_fail("�����������ʹ����Ů���ģ�\n");

	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������ʹ����Ů���ģ�\n");

	message_vision(HIW "$NͻȻ��ɫׯ�أ�˫Ŀ��Σ�����" + 
                       weapon->query("name") + HIW + "������һ���˪���������ˣ�\n\n" NOR,me);
	message_vision(HIW "$N���������̬�ޱ����Ʈ�ݣ��ӽ���$nֱ�̹�ȥ���������ǣ�\n\n"NOR,me,target);

	ap = me->query_skill("sword") + me->query_skill("force");
	dp = target->query_skill("parry") + me->query_skill("force");
	if (mapp(target->query("family")) && target->query("family/family_name") == "ȫ���")
		ap += ap/3;

        if (ap/2 + random(ap) > dp || !living(target))
	{
		damage = ap + random(ap);
		//�жϽ������ͷ�������Ϊ�Ĵ���
		if (!mapp(me->query("couple"))) married = 1;
		else married = me->query("couple/married");
		if (mapp(me->query("sex"))) married += me->query("sex/times");
		damage -= (damage/5) * (married - 1);
		if (damage < 10) damage = 10;
		target->receive_damage("qi", damage/2 + random(damage/2), me);
		target->receive_wound("qi", damage, me);
		msg = HIR "ֻ��$nһ���Һ�����Ȼ��$N��" + NOR + weapon->query("name") + HIR +
                      "���صĴ��У���������������һ���ɫ��˪�����ɪɪ������\n"NOR;
		if (!target->is_busy())
			target->start_busy(1+random(2));
		me->start_busy(2);
	} else
	{
		msg = HIY "$n��״��ʧɫ��˫���أ������ˣ������ܹ�$N��������ľ������Ǵ����졣\n"NOR;
		me->start_busy(2+random(4));
	}
        message_combatd(msg, me, target);
	return 1;
}
