// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// bizhen-qingzhang.c

#include <ansi.h>

inherit SKILL;

string *action_msg = ({
        "$N���μ��Σ�һԾ����$n��ǰ�����ƴ����й�֮������$n��$l",
        "$N����Ծ��˫�����϶���б����������ʱ��ǧ���ƺ���������˷�ϯ��$n",
        "$Nƽ��Ϊ����бб�������ó�һ�������͵��ƾ���쫷�����$n��ȫ��",
        "$N��ת���ƻ�סȫ��������Ծ��$n��ǰ����ע���ƣ�����$n������ȥ",
        "$N���ƺ󳷣�����һ�����͵ػ��ƿ������ó�һ���ޱ��������ƾ�ֱն��$n��$l",
        "$N˫�ֻ�������γ�һ����Ȧ��һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���򲻹����޷���ϰ�������ơ�\n");

        if ((int)me->query("max_neili") < 2500)
                return notify_fail("�������̫�����޷���ϰ�������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("��Ļ����Ʒ���򲻹����޷���ϰ�������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bizhen-qingzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ı������ơ�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "attack": 70  + random(10),
                "dodge" : 70  + random(10),
                "parry" : 70  + random(10),
                "force" : 340 + random(100),
                "damage_type" : random(2) ? "����" : " ����",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 80)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("��������������������ơ�\n");

        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        
        if (damage_bonus < 100) return 0;

        if (random(me->query_skill("force")) > victim->query_skill("force") / 2)
        {
                result = ([ "damage" : (damage_bonus - 100) / 2 ]);
                result += ([ "msg" : HIR "ֻ��$n"
                                     HIR "ǰ�ء����ꡱһ�����������߹���ϵ�������\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bizhen-qingzhang/" + action;
}
