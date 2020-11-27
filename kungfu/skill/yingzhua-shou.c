// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yingzhua-shou.c �ѹ�ӥצ��

inherit SKILL;

string *action_msg = ({
        "$N˫��һ£����צֱ��$n���̣���צȴЮ����֮������$n���䣬һ��һʵ������һ�С���צʽ��",
        "$N���ζ�������ӥ���հ㡰ٿ���ش�$nͷ��Խ����ʹһ�С���צʽ��˫צ����$n�Ժ����",
        "$N�͵�һ����ͻȻ����$n��ǰ��ʹһ�С���צʽ������צֱ��$nС��",
        "$N��צ���أ���צ�����󷢣�һ�С���צʽ������������$n��$l",
        "$N���ι��죬����ǰ�ˣ�ʹһ�С���צʽ����ֱ��$n�ɲ�",
        "$N����Ʈ������Ȼת��$n���һ�С���צʽ����˫צֱ��$n�ʺ����",
        "$Nһ����Х�����ΰ���ʹ����ǧצʽ�����ɰ�������»���$n�پ�����צӰ������ȫ����Ѩ",
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_combine(string combo) { return combo == "hanbing-mianzhang"; }  

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��ӥץ�����ֱ�����֡�\n");

        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷�ѧӥץ�����֡�\n");
                
        if ((int)me->query_str() < 24)
                return notify_fail("��ı���̫��޷�ѧӥץ�����֡�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(120),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"ץ��":"����",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("�������������ӥץ�����֡�\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yingzhua-shou/" + action;
}

