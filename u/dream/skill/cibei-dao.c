// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// cibei-dao.c �ȱ���

inherit SHAOLIN_SKILL;

string *action_msg = ({
        "$N����$wбָ��һ�С�ͣ����·��������һ�٣�һ����$n��$l��ȥ",
        "$Nһ�С�ͯ�ӹһ�������������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
        "$Nչ���鲽������Ծ�䣬һ�С��ƴ����¡�������һ������ն��$n",
        "$Nһ�С����ż�ɽ����$w�󿪴��أ����϶��»���һ���󻡣���ֱ����$n",
        "$N����$wһ����һ�С���Ϫ���㡹��˫�ֳ����������У�����$n���ؿ�",
        "$N����$w��ʹ��һ�С��Ź����ġ����������ã����ҿ�����������$n",
        "$Nһ�С��������ۡ������Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
        "$N����פ�أ�һ�С�������Ϣ�����ӳ�һƬ�����ĵ�Ӱ����$n��ȫ��ӿȥ",
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_combine(string combo) { return combo == "fumo-jian"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("cibei-dao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ĵȱ�������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 90 + random(40), 
                "attack": 40 + random(10),
                "dodge" : 40 + random(10),
                "parry" : 40 + random(10),
                "damage_type": random(2) ? "����" : "����", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("��������������ȱ�����\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("�������������\n");

        if( (int)me->query_skill("luohan-quan", 1) < 30 )
                return notify_fail("����޺�ȭ��Ϊ��������\n");

        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action) 
{
        return __DIR__"cibei-dao/" + action; 
}
