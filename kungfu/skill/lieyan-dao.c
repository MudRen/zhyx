// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// lieyan-dao.c ���浶

inherit SKILL;

string *action_msg = ({
        "$Nһ�С�����������$w����һ��������$n���������Σ�����������仯����",
        "$Nһ�С���ˮǧɽ����������һǰһ��$w����������$n��$lնȥ",
        "$N����Ծ�䣬һ�С���ɨǧ���$w���ż������һ������$n��ɨ��ȥ",
        "$Nһ�С����ҿ�������$w�󿪴��أ����Ҳ�������һ������һ����$n�����翳��",
        "$N����$w���϶��£�һ�С����ɷ��١���������к����һƬѩ���ٲ�����$n��ͷ��",
        "$N����$w��ʹ��һ�С�ֱ���������������ã����ҿ�����ǧ�����������$n",
        "$N���õ��羢����һ�С�����������һ����ת������������$n��$l����ȥ",
        "$N��ǰһ��������һ�С��ϲ���ɽ����$wֱֱ��������һƬ�����ĵ�Ӱ��$n��ȫ����ȥ",
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("shenghuo-shengong", 1) < 20)
                return notify_fail("���ʥ���񹦻��̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(30),
                "attack": 60 - random(10),
                "dodge" : 60 - random(10),
                "parry" : 60 - random(10),
                "damage_type" : "����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("����������������浶��\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("����������������浶��\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}

