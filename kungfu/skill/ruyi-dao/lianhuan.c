//ruyi.c ����������

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

void remove_effect(object me, int a_amount, int d_amount);

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon,ob;
        int skill, amount;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������������ֻ����ս����ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "blade")
                return notify_fail("�������������������õ�����ʩչ��\n");

        if( (int)me->query_skill("ruyi-dao", 1) < 150 )
                return notify_fail("��ġ����⵶����������죬����ʹ�á���������������\n");

        if ( me->query_skill_mapped("blade") != "ruyi-dao")
                return notify_fail("��û�м������⵶�������ϣ�\n"); 

	if ((int)me->query_skill("xiaowuxiang", 1)<150
		&& (int)me->query_skill("lingjiu-xinfa", 1)<150
		&& (int)me->query_skill("xiaoyao-xinfa", 1)<150
		&& (int)me->query_skill("bahuang-gong", 1)<150
		&& (int)me->query_skill("beiming-shengong", 1)<150)
		return notify_fail("��������ڹ��ķ�����ȷ�����߹�������������ʹ��������������\n");

	if ( me->query_skill_mapped("force") != "xiaowuxiang"
		&& me->query_skill_mapped("force") != "bahuang-gong"
		&& me->query_skill_mapped("force") != "lingjiu-xinfa"
		&& me->query_skill_mapped("force") != "xiaoyao-xinfa"
		&& me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("��û��������ң��ϵ���ڹ���\n");	

        if( (int)me->query("neili") < 400  ) 
                return notify_fail("�������������\n");

        skill = me->query_skill("blade");
	amount = ( skill * 2 ) / 10;

	if ( amount < 50 ) amount = 50;
	if ( amount > 120 ) amount = 120;

	me->add_temp("apply/damage", amount);
	me->add_temp("apply/attack", amount*2);
	me->add_temp("apply/dodge", amount*2);

	message_vision(HIY "\n$Nһ����Ц��ֻ���������⣬�������أ��Ĺ�ʲô�Ƿ����裬����һ��������\n"NOR, me,target);   
       	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        me->add("neili", -50);       
        message_vision(HIY "\n$N���浶ת��˳������һ����\n"NOR, me,target); 
       	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        me->add("neili", -50);        
	message_vision(HIY "\n$N�������������δ������������һ����\n"NOR, me,target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        me->add("neili", -50);        
        message_vision(HIY "\n$N������ת������һ���ֻ�ת������\n"NOR, me,target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        me->add("neili", -50);      

	me->add_temp("apply/damage", -amount);
	me->add_temp("apply/attack", -amount*2);
	me->add_temp("apply/dodge", -amount*2);
	me->start_busy(2+random(3));
        target->start_busy(1+random(2));

        return 1;
}
