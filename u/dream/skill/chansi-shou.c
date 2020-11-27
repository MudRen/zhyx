// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;

string *action_msg = ({
        "$N���ƻ�צ����ָ�繳��ֱ��$n������ҪѨ",
        "$N������Σ���������ֱ��������$n�ļ羮��Ѩ",
        "$N��ָ��������ò�ʩ������$n����·Ҫ��",
        "$N����ӥץ�������߾٣�����$n���нڴ���",
        "$N��ǰһ��������˷�����������Ӱ��һצץ��$n���ؿ�",
        "$N���ֻ��ۣ�ȫ��ؽ�žž���죬����$n��$l",
        "$Nʮָ���죬������հ������$n��ȫ��ҪѨ",
        "$N�������ţ���һ�������У�˫��ͬʱ����$n��ȫ�����",
});

int valid_enable(string usage)
{
        return usage == "hand" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����˿�����ֱ�����֡�\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ���򲻹����޷�ѧ��˿�����֡�\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("���������Ϊ̫�����޷�����˿�����֡�\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("��Ļ����ַ��������޷�����˿�����֡�\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("chansi-shou", 1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷���������Ĳ�˿�����֡�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"����":"����",
                "dodge" : 50 + random(10),
                "parry" : 50 + random(10),
                "attack": 50 + random(10),
                "force" : 250 + random(60),
        ]);
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("����������ϰ��\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("���������������˿�����֡�\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chansi-shou/" + action;
}

