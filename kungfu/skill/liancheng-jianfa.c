// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// liancheng-jian.c ���ǽ���

inherit SKILL;

string *action_msg = ({
        "$Nʹһʽ���º躣������������$w����΢�񣬻ó�һ���������$n��$l",
        "$N����ǰ��ʹ�������겻�ҹˡ�������$w����һ����������$n��$l",
        "$N����$wһ����һ�С������մ��졹��ббһ�������ó�������$n��$l",
        "$N���н����ॳ���һ����һʽ����������������һ���������$n��$l",
        "$Nһʽ����������·��������$w�������������ʹ$n�Ѷ���ʵ���޿ɶ��",
        "$N����$wбָ���죬��â���£�һʽ��Ǽ��Թ����������׼$n��$lбб����",
        "$Nһʽ����������š������󼱶�������������⣬����$n��$l",
        "$Nһʽ��ң����ǰ������$w��ն�������缲�������$n���ؿ�",
        "$Nһʽ��������ǧ�ߡ���$wͻȻ���������һƬ���Χ��$nȫ��",
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me) { return 1; }

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(60),
                "attack": 70 + random(10),
                "dodge" : 70 + random(10),
                "parry" : 70 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 80)
                return notify_fail("����������������ǽ�����\n");
        if ((int)me->query("neili") < 80)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liancheng-jianfa/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (! objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("liancheng-jianfa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
