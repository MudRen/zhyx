// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;

string *action_msg = ({
        "$N�ֳ�$wһ�����£�Ѹ���ޱȣ��Ʋ��ɵ�",
        "$N�������¶��ϻ��˸��뻡��$w������£�����$n�ľ���",
        "$N��Ȼ��$w����컨��׹�������ѹ��$n",
        "$Nһ��$w���������Ű�һ����$n��ȥ����ס$n���е���·",
        "$Nת��Ծ������$w�����뵶������һ���������$n",
        "$N����$w���ҿ���ɱ��$w���������׹⣬���·�������$n",
        "$N��$wʹ�ú����·������ذ���أ�ƫ����ó��棬$wЮ��������$n��$l",
        "$N���һ�������е�$w���糤��һ����$nֱ������",
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 600)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < 60)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ��ʤ������\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("baisheng-daofa", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������İ�ʤ������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(30), 
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2) ? "����" : "����", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("������������������˰�ʤ������\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("������������������˰�ʤ������\n");

        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baisheng-daofa/" + action;
}
