// lunhui.c �����ȷ����У��ֻ�����
// By Alf, Last Update 2001.10

#include <ansi.h>

int perform(object me, object target)
{
    object weapon;
        string msg;
    int damage,sk1,sk2,exp1,exp2,stf;

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("���ֻ�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    sk1 = (int)me->query_skill("staff");
    if(target->query_skill_mapped("parry")==target->query_attack_skill())
        sk2 = ((int)target->query_skill("parry")+(int)target->query_skill("dodge"))/2;
    else
        sk2 = ((int)target->query_skill("parry",1)+(int)target->query_skill("dodge"))/2;
    exp1 = (int)me->query("combat_exp");
    exp2 = (int)target->query("combat_exp");
    stf = (int)me->query_skill("liudao-zhang",1);
        
    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "staff")
        return notify_fail("��ʹ�õ��������ԡ�\n");
                
    if(stf < 100 )
        return notify_fail("��������ȷ�������죬�޷�ʹ�����ֻ���������\n");
                                
    if( (int)me->query("neili", 1) < 300 )
        return notify_fail("����������̫��������ʹ�á��ֻ���������\n");

    msg = 
HIY"$NͻȻ���һ��������һͦ�������ᴦ��"+weapon->name()+HIY"ȥ���������$n���ؼ��̣�\n"NOR;

    if (random(sk1*sk1*sk1/1000+exp1/100) > (sk2*sk2*sk2/2000+exp2/200) || !living(target))
    {
        if(stf<300)
            target->start_busy( stf / 40 + random(2));
        else
            target->start_busy(4);
                
        damage = (int)me->query_skill("liudao-zhang", 1);
        damage = damage +  stf;
        damage = damage +  (int)me->query_skill("stf", 1);

        target->receive_damage("qi", damage*1/2,me);
        target->receive_wound("qi", damage/3,me);
        me->add("neili", -400);
        me->start_busy(3);
        msg += HIM"$nֻ����һ������ǰ��"+weapon->name()+HIM"���˸��Դ������ɳ����Һ���\n"NOR;
    }

    else
    {
        msg += YEL"����$n���з�����������������$N����һ�����׻��⡣\n"NOR;
        me->add("neili", -100);
        me->start_busy(4);
    }

    message_vision(msg, me, target);
    if(!userp(target)&& !target->is_killing(me->query("id")) ) target->kill_ob(me);
    return 1;
}

