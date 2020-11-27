// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// tangshi-jianfa.c

inherit SKILL;

string *action_msg = ({
        "$N��ǰ����һ����ͬʱ���д�һ����һʽ�����̺�������ֱ��$n��$l",
        "$N��ǰ������һ�С�������СС����$w��ǰ���$n��$l",
        "$N���ַ��ڶ�����棬�·�������ʲô��һ�С������羪�硹�������е�$w��ǰ����$n��$l",
        "$Nһʽ����ɽ�����ӡ�������$w�Ľ�����һ�Ⲽһ������$n��$l",
        "$N$w��ǰһ�ᣬһ�С��Ǻ᲻�ҹ�����$w����$n",
        "$N���һ����һ�С������д�㡹��������$n������$w�漴�̳�",
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(20),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
                
        if ((int)me->query("qi") < 70)
                return notify_fail("��ľ�����������ʬ������\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("���������������ʬ������\n");
                
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}


