// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;
#include <ansi.h>

string *action_msg = ({
        "$N�����ϲ���һʽ��"+YEL+"��ȴ�"+NOR+"���������ַֿ�����ȭΪ�ƣ�����$n��$l",
        "$N�����̤��ȫ����ת��һ�С�"+RED+"��������"+NOR+"���������͵ز���$n��$l",
        "$Nʹһ�С�"+HIB+"�ຣ��ͷ"+NOR+"��������ǰ̽��˫�ֻ��˸���Ȧ������$n��$l",
        "$N˫�ƻ�����һ�ǡ�"+HIY+"��ͷ�ǰ�"+NOR+"�����Ƴ���磬һ�����е�$n������",
        "$Nʩ����"+WHT+"�ຣ�ޱ�"+NOR+"����˫ȭȭ����磬ͬʱ����$nͷ���أ�������Ҫ��",
});
int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("ѧ���Ʊ�����֡�\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷������ơ�\n");
        if (me->query_skill("strike", 1) <= me->query_skill("dabei-zhang", 1))
                return notify_fail("��Ļ����������޷���������ļ��ɡ�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force" : 300 + random(30), 
                "attack": 50 + random(10), 
                "dodge" : 50 + random(10), 
                "parry" : 50 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����Ʊ�����֡�\n");
                
        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");
                
        if ((int)me->query("neili") < 60)
                return notify_fail("����������������ơ�\n");
                
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dabei-zhang/" + action;
}

