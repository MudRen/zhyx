// xunlei.c �����־��У�Ѹ�ײ����ڶ�
// By Alf

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    int damage;
    string msg;

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
   return notify_fail("��Ѹ�ײ����ڶ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if( (int)me->query_skill("yunlong-shengong", 1) < 100 )
   return notify_fail("��������񹦻����ǳ��ʹ������Ѹ�ײ����ڶ�����\n");

    if( (int)me->query_skill("benlei-shou", 1) < 100 )
   return notify_fail("��ı����ֻ��������죬�޷�ʹ����Ѹ�ײ����ڶ�����\n");

    if( (int)me->query("neili") < 500 )
   return notify_fail("���������Ϊ�������ߡ�\n");

    msg = HIY "
$NͻȻ��߳һ��������������ʩչ����Ѹ�ײ����ڶ�����˫������ɽ�����㹥��$n��\n"NOR;  

    if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3) { 
      me->start_busy(3);
   target->start_busy(random(3));

   damage = (int)me->query_skill("benlei-shou", 1)/2+(int)me->query_skill("unarmed",1)/3;

   damage = damage + random(damage);

   target->receive_damage("qi", damage);
   target->receive_wound("qi", damage/2);
   me->add("neili", -300);
   msg += HIR"
$n��ܲ�������$N��һ�л��õ����˳�ȥ�����ڿ��У������ѿ�����Ѫ��\n"NOR;
    } else
    {
       me->start_busy(1);
       msg += HIG"$n��֮�£���ⷢ������������ݣ����ձܹ���$P��һ����\n"NOR;
    }
    message_combatd(msg, me, target);

    if(!target->is_fighting(me)) target->fight_ob(me);
    if(userp(target)) target->fight_ob(me);
    else if( !target->is_killing(me) ) target->kill_ob(me);
    return 1;
}



