// ding-unarmed.c һ��һ��ȭ

inherit SKILL;

string *action_msg = ({
        "$N��������һĨ����$n��$l��ȥ",
        "$N����һ�ᣬ����$n��$l",
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 210 + random(50), 
                "attack": 30 + random(10), 
                "dodge" : 30 + random(10), 
                "parry" : 30 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 40)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("�������������һ��һ��ȭ��\n");
        me->receive_damage("qi", 30);
        me->add("neili", -30);
        return 1;
}


