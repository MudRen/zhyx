// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// chongling-jian.c ���齣��

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С���÷�綹��������$w���������$n��$l",
        "damage" : 105,
        "parry"  : 40,
        "dodge"  : 45,
        "attack" : 47,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ������Ҷ��ü��������$wƮ������������$n��$l",
        "damage" : 130,
        "parry"  : 40,
        "dodge"  : 45,
        "attack" : 47,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С����г�������$w����ǧ�ٽ�Ӱ����$n������ȥ",
        "parry"  : 40,
        "dodge"  : 45,
        "attack" : 47,
        "damage" : 115,
        "damage_type" : "����"
]),
([      "action" : "$N��ǰ����һ��������$wʹ�������է�꡹ֱ��$n��$l",
        "parry"  : 49,
        "dodge"  : 48,
        "attack" : 42,
        "damage" : 120,
        "damage_type" : "����"
]),
([      "action" : "$N���е�$wһ�Σ��ų�������������ʹ����ͬ��������ֱ��$n�������Ѩ",
        "parry"  : 40,
        "dodge"  : 45,
        "attack" : 50,
        "damage" : 135,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("zixia-shengong", 1) < 20)
                return notify_fail("�����ϼ�񹦻��̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("chongling-jian",1);
        for( i = sizeof(action); i > 0; i-- )
                if( level > action[i-1]["lvl"] )
                {
                        return action[NewRandom(i, 20, level/5)];
                }
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("����������������齣����\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chongling-jian/" + action;
}


