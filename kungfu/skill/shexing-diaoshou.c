// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// shexing-diaoshou ���ε���

#include <ansi.h>
#include <combat.h>
inherit SKILL;

string *action_msg = ({
        "$N���ƻ��أ��ұ�΢�������Σ��������⼲�죬һʽ�����߳���������$n��$l",
        "$N���һ��ʹ������ͷ��β����������������У����ִ�$n���벻��֮����ץ��$l",
        "$Nʹ�����������㡹��˫����$nץȥ��ͬʱ��������Ϣ��һ������$n��$l",
        "ֻ��$N�����ڵأ�����$n��ǰ̽�ӣ�ͻȻ����ʹ����������Ӱ������$n��ץ����",
        "$NͻȻ��ͷ���ӣ���ȴĪ������ع���$n���������Ĺ��ƣ���һ�С�������ܡ�",
        "$Nһʽ����ӥ��������˫�ִ���˻˻�ƿ�֮��������Ѹ�ٵؾ���$n����Ҫ������",
        "$N˫�ֻ����лó������Ӱ��һ�С�������ӿ������������������ǵ�����$n",
        "$N���䲻���ʹһʽ���������š�������ʳ����ָ΢�֣���������$n��$l��ͱ",
        "ͻ��$N˫�������޹ǵ������ţ�ʹ�����������񡹲�ס$n���ұ�ȴ���ĵشӲ���˼�鴦Ĩ��$n��$l",
});
int valid_enable(string usage) { return usage == "hand" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����ε��ֱ�����֡�\n");
               
        if (me->query("family/family_name") == "ŷ������") 
        {
                if ((int)me->query_skill("hamagong",1) < 15)
                        return notify_fail("��ĸ�󡹦��򲻹����޷�ѧ���ε��֡�\n");
        }
        else if ((int)me->query_skill("huntian-qigong", 1) < 15)
                return notify_fail("��Ļ���������򲻹����޷�ѧ���ε��֡�\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷������ε��֡�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 210 + random(60),
                "attack": 40 + random(10),
                "dodge" : 40 + random(10),
                "parry" : 40 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("����������������ε��֡�\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"shexing-diaoshou/" + action;
}

              

