// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit SKILL;

string *action_msg = ({
        "$N����һ�һ�С�ŰĿ��������$w���ñ�ֱ��ֱ��$n��˫��",
        "$N������ң�һ�С��˸Ρ�������$w��������Ӱ����ɨ$n����",
        "$N��������һ�С����ġ�������$w��һ��ͭ����ֱ��$n�ز�",
        "$N����һ�ӣ�һ�С��ߵ���������$wֱ����$n����",
        "$N�߸�Ծ��һ�С����ǡ�������$w��ֱ��$n��ͷ����",
        "$N����һת��һ�С��ջ꡹������$w��������ڿ�һ���͵���$n��ͷ����",
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;

        if ( !objectp(weapon = me->query_temp("weapon"))
        || ( string)weapon->query("skill_type") != "whip" )
                return notify_fail("���������һ�����Ӳ�����ϰ��������\n");

        if( (int)me->query("max_neili") < 400 )
                return notify_fail("����������㣬û�а취��ϰ��������\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("whip", 1) < 60)
                return notify_fail("��Ļ����޷����̫ǳ��\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("chanhun-suo", 1))
                return notify_fail("��Ļ����޷�ˮƽ���ޣ��޷���������Ĳ�������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 110 + random(20),
                "attack": 50 + random(10),
                "dodge" : 50 + random(10),
                "parry" : 50 + random(10),
                "damage_type" : random(2)?"����":"����", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("���������������������\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("���������������������\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chanhun-suo/" + action;
}

