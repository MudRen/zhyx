// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ruyi-dao.c ���⵶
// ��ң�ɵĿ����书��������������ǿ������⵶���������Ϊһ��ǿ��

#include <ansi.h> 
inherit SKILL;

mapping *action_msg = ({
        "$N����$wбָ��һ��"HIY"��˫��˫�ɡ�"NOR"����ת$w���Ե�����$n��$l��ȥ",
        "һʽ"HIR"������������"NOR"��$N���ֳֵ����������������$w��������������$n��$l",
        "$N����ʹ��"HIW"��������Ϭ��"NOR"����Ȼ������Ȼ�����ֳ�$w��һ������Ϯ������������һ��������ն��$n",
        "$Nһ��"MAG"���������ԡ�"NOR"��$w��Ӱ���ε��ٷ���һ������ֱ����$n��$l",
        "$Nһʽ"HIG"������ʯ�á�"NOR"��һ������˫�ֽ���$w�������б��$n��$l",
        "$N����$w��һ��"HIC"������������"NOR"������������ÿһ���������ͽǶȶ���ͬ��������أ���������$n",
        "$Nһ��"HIW+BLK"��Я�����ġ�"NOR"����Ծ��֮�ƣ�����˫���˵���$w�ƿն��£�Ю��������$n��$l�����������ƿյĵ�Х��",
        "$Nһ��"HIR"����"NOR+MAG"��"NOR+HIG"��"NOR+HIY"��"NOR+HIR"��"NOR"����������˫�ֲ�ס����$w��ÿ�����߾ٹ�ͷ��ʱ��ֱ����ʱ��б��",
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
             int level; 
           level = me->query_skill("riyi-dao", 1); 
        if ((int)me->query_skill("xiaowuxiang", 1) < 25
                && (int)me->query_skill("bahuang-gong", 1) < 25
                && (int)me->query_skill("beiming-shengong", 1) < 25)
                return notify_fail("�����ң���ڹ���򲻹����޷�ѧϰ���⵶��\n");
                
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷�ѧϰ���⵶��\n");
            if (me->query_skill("blade", 1) < level) 
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ���⵶��\n");
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
                
        if ((int)me->query("qi") < 60)
                return notify_fail("����������������⵶��\n");
                
        if ((int)me->query("neili") < 60)
                return notify_fail("�������������\n");
                
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"ruyi-dao/" + action;
}

