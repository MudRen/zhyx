// po.c �������ƾ��У�������
// By Alf

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    object weapon;
    int damage, dp;
    string msg;

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if( (int)me->query_skill("bizhen-zhang", 1) < 100 )
        return notify_fail("��ı������Ʋ�����죬����ʹ�������ơ�\n");

//    if( (int)me->query_skill("zixia-shengong", 1) < 80 )
//        return notify_fail("�����ϼ�񹦵ȼ��������޷�ʹ�������ơ�\n");

    if( (int)me->query("neili", 1) < 300 )
        return notify_fail("����������̫����ǿʹ�������������棡\n");

    msg = HIG "$N˫���������ɣ��û���һ����Ӱ��ͻȻ���������£���Ϯ$n����Ҫ����\n"NOR;

    if (living(target))
           dp = target->query_skill("force")/2;
    else    dp = 0;

    if (random(me->query_skill("force")) > dp )
    {
        me->start_busy(1);

        damage = (int)me->query_skill("bizhen-zhang", 1) + (int)me->query_skill("force",1);
        damage = damage/2 + random(damage/2) ;

        target->receive_damage("qi", damage);
        target->start_busy(4);
        me->add("neili", -300);

        msg += HIR"$nֻ��ȫ���Ѩ������̣���ͷһ�𣬿�����Ѫ����������\n"NOR;

    }

    else
    {
        me->start_busy(3);
        msg += CYN"$n���Ʋ����æ�ŵ�һ�����Ǳ���״�ı��˿�ȥ��\n"NOR;
    }
    message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        if(userp(target)) target->fight_ob(me);
        else if( !target->is_killing(me) ) target->kill_ob(me);
    return 1;
}


