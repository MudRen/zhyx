// Code by JHSH
// ���޵�����

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object ob;
        string msg;
        int intBT;

        if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("���޵�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( !living(target) )
		return notify_fail("������û�б�Ҫʹ�����޵����ơ�\n");

	if( me->query_temp("weapon"))
		return notify_fail("�㲻���±���������ܹ�ʹ����Ůȭ����\n");

	if( (int)me->query_skill("meinv-quan", 1) < 100 )
		return notify_fail("�����Ůȭ��������죬ʹ�������޵����ơ�\n");

	if( (int)me->query_skill("yunv-xinfa", 1) < 120 )
		return notify_fail("�����Ů�ķ���Ϊ������ʹ�������޵����ơ�\n");

	if( me->query("neili") <= 300 )
		return notify_fail("�����ڵ�����������ʹ�����޵����ƣ�\n");

	if( me->query("jingli") <= 100 )
		return notify_fail("�����ڵľ�������ʹ�����޵����ƣ�\n");

	if( me->query_skill_mapped("parry") != "meinv-quan" )
		return notify_fail("����мܲ�����Ůȭ��, �޷�ʹ�����޵����ơ�\n");

	if( me->query_skill_mapped("force") != "yunv-xinfa" &&
	    me->query_skill_mapped("force") != "nuhai-kuangtao")
		return notify_fail("�����õ��ڹ�����, �޷�ʹ�����޵����ƣ�\n");

	me->add("neili", -50);
	me->add("jingli", -50);

        msg = "\n"+HIW"\nֻ��$N˫�۷��裬������죬��ֻ�������ƻ�����ǧ��ǧ��������$n����ǰ��һ��һʽ��������Գɶ��䡣\n"NOR;

	if( random(me->query("combat_exp")) > random(target->query("combat_exp")) * 2)
	{
		msg += HIC"ֻ��$N˫�ֻû�������ȭӰ��û��$n���׵�ʱ���Ѿ���$Nȭ����ס��ȫ���붯Ҳ�������ˣ�\n"NOR;
                intBT = (int)me->query_skill("meinv-quan") / 25;
		if (intBT > 20) intBT = 20;
		target->start_busy(intBT);
	}
        else if( random(me->query("combat_exp")) > random(target->query("combat_exp")))
	{
		msg += HIC"$n��$NͻȻȭ������Ŀ죬���˷�����˼������һ���������Ӷ�����Ӱ��Χ�ˣ�\n"NOR;
        intBT = (int)me->query_skill("meinv-quan") / 50;
		target->start_busy(intBT);
		if (intBT > 10) intBT = 10;
	}
        else
        {
                message_vision(HIB"\n$nͻȻ����$N����ͻ�䣬�о�������ʱ��������û��������Ӱ֮�У�\n"NOR, me, target);
                intBT = random(4);
                me->start_busy(4 + intBT);
        }
        message_vision(msg+"\n", me, target);
        return 1;
}
