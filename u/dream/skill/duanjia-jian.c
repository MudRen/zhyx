// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// duanjia-jian.c �μҽ�

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N�������˸�����������$wƽƽ�ݳ���һʽ��"HIY"�����Ͻ�"NOR"��ֱ��$n��ǰ��",
        "$N������ǰ��$w��һ���벻���ĽǶ�ͻȻ������һʽ��"HIG"�̼�����"NOR"��ֱ��$n������",
        "$Nһ�С�"HIY"�����ڿ�"NOR"��������Ծ�ڰ�գ�$w��������?��ֱ��$n��ͷ��",
        "$N����б�ӣ�����ָ��$n�ĸ�����һ�С�"HIG"��Ԩ����"NOR"�������¶��ϣ�����$n",
        "$N˫����أ�б�ɶ�����$w����$n��$l,��һ�С�"HIG"Цָ����"NOR"��",
        "$N��Хһ�����ὣ�������͸������֮�⣬���ǶμҲ���֮�ء�"HIY"��¹��ԭ"NOR"����������ס$n��ȫ��",
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("kurong-changong", 1) < 20)
                return notify_fail("��Ŀ����������̫ǳ��\n");
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
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 70)
                return notify_fail("��������������μҽ�����\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duanjia-jian/" + action;
}

