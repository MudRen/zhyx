//���佣�� ����޼� wuji.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra,i;
        string *style = ({ 
HIM "$N�ֳ�$w��ǰ����һ���裬����$w��Ȼ����$n��"NOR,
HIM "$N�ŵ�һ��������$w�������Ѵ���$nС����"NOR, 
HIM "$N������ס$w������һ���׻�������ֱָ$nü�ģ�"NOR,
HIM "$N��ǰһ�ݣ����˰벽��ͻȻһ������������$w��$n���˹�ȥ��"NOR,
HIM "$N��$w�϶�Ϊһ���������ͦ�����$n������Ҫ����"NOR, 
HIM "$N������һ������������$w�������£�����$n���̣�"NOR, 
HIM "$N����һԾ������$w�������죬����$n����������"NOR, 
HIM "$N����$w���ӣ������������⣬����һת��Ѹ�ٴ���$n��"NOR
});
        object weapon,*obs;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������޼���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(!pointerp(obs=me->query_team()) || !me->is_team_leader())
                return notify_fail("ֻ�ж�������ſ��Է�����ʽ��\n");

        if(me->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("�㻹û��׼�������佣��\n");

        if(me->query_skill("zhenwu-array",1) < sizeof(obs)*20 ) 
                return notify_fail("������佣������Ϊ������\n");

        if(sizeof(obs) > 8 )
                return notify_fail("����������ֻ���ɰ˸�����ɣ�\n");

        for( i = 0; i < sizeof(obs); i++ ) 
        { 
           if(!obs[i]) 
                return notify_fail("��Ķ����������뿪����Ҫ������϶��顣\n");

           if(environment(obs[i]) != environment(me)) 
                return notify_fail("��Ķ����Ա��ȫ������ߡ�\n");

           if(obs[i]->query_skill("zhenwu-array",1) < 80 ) 
                return notify_fail("����������˵����佣���󷨻�δ���š�\n");

           if (! objectp(weapon = obs[i]->query_temp("weapon")) || 
                (string)weapon->query("skill_type") != "sword") 
                return notify_fail("��Ķ���������û��װ������\n"); 

           if(obs[i]->query_skill("sword",1) < 120 ) 
                return notify_fail("��Ķ��������˵Ļ�����������̫�͡�\n");

           if(obs[i]->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("��Ķ���������δ׼�������佣���󷨣�\n");
        } 

        message_vision(HIG "ֻ��$Nһ����Х������" + weapon->name() +
                       HIG "һ�����������ų����佣��֮������޼���ʽ��ͦ����$n" 
                       HIG "��ȥ��\n"NOR,me,target);

        for (i = 0; i < sizeof(obs); i++ ) 
        {
           weapon=obs[i]->query_temp("weapon");
           msg = style[i];
           extra = obs[i]->query_skill("sword", 1) / 10; 
           extra *= (i+1); 
           obs[i]->add_temp("apply/attack", extra);
           obs[i]->add_temp("apply/damage", extra);
           COMBAT_D->do_attack(obs[i],target, weapon, 0,msg);
           obs[i]->kill_ob(target); 
           obs[i]->add_temp("apply/attack", -extra);
           obs[i]->add_temp("apply/damage", -extra);
           obs[i]->start_busy(3);
        }
        return 1;
}

