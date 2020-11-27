// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;

string *action_msg = ({
        "$N˫��һ��һ�С������������ó������Ӱ����$n��$l",
        "$N����һ����������Ȼ�Ƴ���һ�С��ؾ��쳤��ǿ�����Ʒ�ֱ��$n��$l",
        "$N˫�Ʒ׷ɣ�һ�С�����Ϸˮ��ֱȡ$n��$l",
        "$N��������λ���ߣ�һ�С����︴�ա��������Ʒ��޿ײ����ػ���$n��$l",
        "$N�������˫��ƽ�ƣ����������һ�С��عⷴ�ա�����$n��$l",
        "$N����������ǰ�������Ƴ���һ�С����է�֡�ѸȻ����$n$l",
        "$Nʹ��������ǧ���������μ�����������$n���ƹ���",
        "$Nһ�С����ξ��졹��˫������ʵʵ�Ļ���$n��$l",
        "$N���ƻ��˸�ȦȦ�������Ƴ���һ�С�������λ������$n$l",
});

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("���������Ϊ���㣬�޷����������ơ�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�ѧ�������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chongyang-shenzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�����������������ơ�\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "zhongnan-zhi";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(50), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

        if ((int)me->query("neili") < 65)
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

        me->receive_damage("qi", 60);
        me->add("force", -55);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chongyang-shenzhang/" + action;
}
