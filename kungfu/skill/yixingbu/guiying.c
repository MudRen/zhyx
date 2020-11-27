// guiying.c
// smallbear 11/1/2002

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
      object weapon;
      int skill;
    if( !target ) target = offensive_target(me);

    if( !target || !me->is_fighting(target) )
      return notify_fail("�����ι�Ӱ��ֻ����ս����ʹ�á�\n");

    if ((int)me->query_skill("yixingbu", 1) < 100 )
        return notify_fail("������β����ȼ�����������ʹ�������ι�Ӱ����\n");    
    if ((int)me->query_skill("dodge", 1) < 100 )
        return notify_fail("��Ļ����Ṧ��������죬����ʹ�������ι�Ӱ����\n");    
    if ( me->query_skill_mapped("dodge") != "yixingbu"
             || me->query_skill_mapped("force") != "busi-shenlong") 
                return notify_fail("�������޷�ʹ�������ι�Ӱ������ǣ�ƣ�\n"); 
    if ((int)me->query("neili") < 300 )
        return notify_fail("����������̫��������ʹ�������ι�Ӱ����\n");
    if ((int)me->query("neili") < 1000 )
        return notify_fail("����������̫��������ʹ�������ι�Ӱ����\n");
    if ( (int)me->query_temp("��Ӱ", 1) ) 
        return notify_fail("���Ѿ�ʹ�������ι�Ӱ��������\n");
    
    message_vision(HIB"$Nǰ�����ߣ�������������̤���β����������������Ρ�
$n���ˡ����ι�Ӱ�����Ի������޴룬��֪�ĸ�$N���棬�ĸ��Ǽ١�\n"NOR, me, target);
    target->start_busy(4);
    me->start_busy(2);
    me->add("neili", -200);    
    skill = me->query_skill("yixingbu", 1)/3;
    me->set_temp("��Ӱ", 1);
    me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), skill+1);
    return 1;
}

void remove_effect(object me)
{
    message_vision(HIB"$N����һ������������������������ʧ������\n"NOR, me);
    me->delete_temp("��Ӱ");
    return;
}

