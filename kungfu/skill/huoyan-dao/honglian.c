// honglian.c ���浶  ������
// by looo 2001/6/21

#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int amount);

int perform(object me)             
{
        int count, skill;
        skill = me->query_skill("longxiang");
/*
        if( !me->is_fighting() )
                return notify_fail("��������ֻ����ս���е�ʹ�á�\n");
*/

        if(objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ������á������𡹣�\n");
        if(me->query_temp("honglian"))
                return notify_fail("������ʹ�á������𡹡�\n");

        if((int)me->query_skill("huoyan-dao", 1) < 180 )
                return notify_fail("��Ļ��浶������죬��������ᡸ������֮���ϡ�\n");
        if ( me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("�����ʹ�û��浶��ʩչ�������𡹡�\n");
        if( (int)me->query("max_neili", 1) < 1500 )
                return notify_fail("���������Ϊ̫����ʹ�����������𡹡�\n");
        if( (int)me->query("neili", 1) < 800 )
                return notify_fail("����������������ʹ�����������𡹡�\n");
        if(userp(me) && (int)me->query_skill("longxiang", 1) < 100 )
                return notify_fail("�����������񹦵ȼ������ߣ�ʹ�����������𡹡�\n");
         if ( me->query_skill_mapped("force") != "longxiang" && me->query_skill_mapped("force") != "xiaowuxiang") 
                return notify_fail("����ʹ�ڹ��ڻ��浶�ķ�������ʹ�����������𡹡�\n");
        if(userp(me) && (int)me->query_skill("lamaism", 1) < 150 )
                return notify_fail("��������ķ������򲻹����޷�ʹ�á������𡹡�\n");

        me->receive_damage("qi", 0);
        message_combatd(RED"\n$N" RED "������浶֮�������𡹾����������������ʺ�ɫ����ӿ��������ǰ����֮��\n"
                        RED "Ʈ���޶����������ڰ�գ�������翣�����׽����\n"NOR,me);
        count = skill / 2;


        me->add("neili", -300);
        me->add("jing", -50);
        me->add_temp("apply/attack", count);
        me->add_temp("apply/strike",count/2);
        me->set_temp("honglian", 1);
        me->start_call_out( (: call_other,  __FILE__, "remove_effect", me, count :), skill/3 );

        return 1;
}

void remove_effect(object me, int amount)
{
        if ( (int)me->query_temp("honglian") )
        {
                me->add_temp("apply/attack", -amount);
                me->add_temp("apply/strike", -amount/2);
                me->delete_temp("honglian");
                tell_object(me,HIR "����ǰƮ���޶��Ļ���������ȥ��\n"NOR);
        }
}
