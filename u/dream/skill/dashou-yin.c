// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// dashou-yin ���ڴ���ӡ

inherit SKILL;

string *action_msg = ({
        "$Nһʽ����������ӡ����˫�����࣬Ĵָ��Сָ���������΢Ц���۽�$n����ǰ��ӡ��$n��$l",
        "������$N��ָ���壬Ĵָ����΢�֣��ֽᡸ���ƹ���ӡ������$n��ͷ���£��Ʋ��ɵ�",
        "$Nʹһʽ��׼���ĸӡ������ָ���棬ʳָ���죬������˼״��ͻȻ�������ӡ����$n��$l",
        "$N�ֽᡸ��������ӡ��������ŭ����������š���һ��ʤ���䣬������һ��һ�ã�׽��$n������·",
        "ȴ��$N˫����ȭ��ʳָǰ�죬������������һʽ��ҩʦ�����ӡ������$n��$l�ܹ�ȥ",
        "ֻ����$N���������󳪣���ɫׯ�ϵ�ʩչ�����½��ӡ����˫�ֽ��棬Ĵָ�����һ�¿�ס$n�羮��Ѩ������$n����һˤ",
        "$N�渡΢Ц��˫�ֻ��գ������ഥ��һ������$n����ǰ��һʽ�����ֽ��ӡ����ס$n����������һ��",
        "$Nһʽ�������ǻ�ӡ����������������������䣬˫��һ����ס$n�첲�����˳��һ��",
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "yujiamu-quan"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����ڴ���ӡ������֡�\n");

        if ((int)me->query("max_neili") < 350)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("lamaism", 1) < 20)
                return notify_fail("��������ķ���֪ʶ�˽�̫�٣��޷�������ڴ���ӡ��\n");

        if ((int)me->query_skill("lamaism", 1) < (int)me->query_skill("dashou-yin",1))
                return notify_fail("���������ķ�֪ʶ��֪ʶ���ޣ����Խ�һ���������ӡ��\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("dashou-yin",1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷�������������ڴ���ӡ��\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(120), 
                "attack": 70 + random(10), 
                "dodge" : 70 + random(10), 
                "parry" : 70 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 80)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 80)
                return notify_fail("����������������ڴ���ӡ��\n");
        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dashou-yin/" + action;
}

