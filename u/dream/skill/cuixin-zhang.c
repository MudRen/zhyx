// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// cuixin-zhang.c ������

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N���ر�צΪ�ƣ����β������ұ۶�������������һ�Ƴ�$n$l��ȥ",
        "$N���Ƽ��ϣ�˫��ֱ��ֱ�£�Ʈ�����������Ŵ��һ����˫��ͬʱ�Ƴ�",
        "$N˫�Ʋ�ס���趯��ֻ����������һ�����죬����һ������������$n$l��ȥ",
        "$N���δ춯���������������ų�$n�������ƣ�һ�ƿ���һ�ƣ�һ������һ��",
        "$Nһ����Х������Ʈ�磬����������е�ֿ���ĳ�����δ������������Ѹ���Ѽ�",
});

int valid_enable(string usage) { return usage == "strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="jiuyin-baiguzhao"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");
                
        if ((int)me->query("max_neili") < 500)
                return notify_fail("�������̫�����޷��������ơ�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(90), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        return notify_fail("û�о����澭������������������������ơ�\n");
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("cuixin-zhang", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"cuixin-zhang/" + action;
}
