// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// jingang-chu.c, ��ս�ħ��

inherit SKILL;

string *action_msg = ({
        "$N��ɫׯ�ϣ�������ţ�ʹ��һ�С����������������$wɨ��$n��$l",
        "$N����ŭ�ݣ����д�ȣ���̤��һʽ����շ�ħ����$w����$n��ͷ����",
        "$Nһ�С���������������������дʣ���Ȼ�۷���⣬��������$w��ɨ$n��$l",
        "$Nһ�С���Ȥ��������������$w����չ�������Ľ��䣬���ۻ�$w����$n��$l",
        "$Nһʽ���������ޡ����ڳ��ֻؾ������ȷ�����$w��β���ػ���$n",
        "��Ȼ��$Nһ������֮ɫ������$w�����뻡ʹ��������Ѫ����������$n��$l",
        "$Nһʽ��������ħ�������������������ԣ���$w���һƬ������$n��������",
        "$N��Ŀ������������������һ�����ʩչ����ħ������������$w���Ƴ����ֱ����$n��$l",
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 80)
                return notify_fail("�������������\n");
                
        if ((int)me->query_skill("staff", 1) < 
            (int)me->query_skill("jingang-chu", 1))
                return notify_fail("��Ļ����ȷ����̫ǳ��\n");
        
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(30), 
                "attack": 40 + random(10), 
                "dodge" : 40 + random(10), 
                "parry" : 40 + random(10), 
                "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :),
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        ||  (string)weapon->query("skill_type") != "staff")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if (me->query_str() < 20)
                return notify_fail("��ı�����������ս�ħ�ơ�\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("���������������ս�ħ�ơ�\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("���������������ս�ħ�ơ�\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
}

string perform_action_file(string action)
{
        return __DIR__"jingang-chu/" + action;
}

