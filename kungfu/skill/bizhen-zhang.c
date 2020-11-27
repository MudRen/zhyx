// bizhen-zhang.c ��������
// By Alf


inherit SKILL;

mapping *action = ({
([    "action" : "$Nһʽ�����׽ӿձ̡���˫�Ƽ�����һ�ŵ�������������������$n��$l",
    "force" : 130,
    "dodge" : 20,
    "damage": 10,
    "lvl" : 0,
    "skill_name" : "���׽ӿձ�",
    "damage_type" : "����"
]),
([    "action" : "$Nһʽ���������˳����������������˫��һ��һ�ͣ���$n�޷�����",
    "force" : 150,
    "dodge" : 10,
    "damage": 30,
    "lvl" : 20,
    "skill_name" : "�������˳�",
    "damage_type" : "����"
]),
([    "action" : "$Nʹһʽ�����������Ρ�������΢��������է��է�ϣ��͵ز���$n��$l",
    "force" : 150,
    "dodge" : 30,
    "damage": 40,
    "lvl" : 30,
    "skill_name" : "����������",
    "damage_type" : "����"
]),
([    "action" : "$N˫������������һʽ���������ˡ���������������������$n��ȥ",
    "force" : 250,
    "dodge" : 20,
    "damage": 55,
    "lvl" : 40,
    "skill_name" : "��������",
    "damage_type" : "����"
]),
([    "action" : "$N�������ݣ�ʹ��һʽ���������ড���˫�Ʋ�£����ֱ�ز���$n��$l",
    "force" : 300,
    "dodge" : 25,
    "damage": 70,
    "lvl" : 60,
    "skill_name" : "��������",
    "damage_type" : "����"
]),
([    "action" : "$N����΢�Σ�һʽ��������δ�ݡ�չ����˫��Ю��쪾�������Ȼ����$n",
    "force" : 350,
    "dodge" : 30,
    "damage": 85,
    "lvl" : 70,
    "skill_name" : "������δ��",
    "damage_type" : "����"
]),
([    "action" : "$N�������أ�������ӯ��ʹ��һʽ��ĺ���¿�������ͬʱ��$n��$l��ȥ",
    "force" : 350,
    "dodge" : 30,
    "damage": 100,
    "lvl" : 80,
    "skill_name" : "ĺ���¿���",
    "damage_type" : "����"
]),
([    "action" : "$Nͻ��һ�С�������ǰ·����˫��������ò�����һǰһ��ĳ�$n��ȥ",
    "force" : 450,
    "dodge" : 30,
    "damage": 120,
    "lvl" : 100,
    "skill_name" : "������ǰ·",
    "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("���������Ʊ�����֡�\n");
//    if ((int)me->query_skill("zixia-shengong", 1) < 20)
//        return notify_fail("�����ϼ�񹦻�򲻹����޷�ѧ�������ơ�\n");
    if ((int)me->query("max_neili") < 100)
        return notify_fail("�������̫�����޷����������ơ�\n");
    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("bizhen-zhang",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 30)
        return notify_fail("�������̫���ˡ�\n");
    if ((int)me->query("neili") < 40)
        return notify_fail("��������������������ơ�\n");
    me->receive_damage("qi", 25);
    me->add("neili", -10);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"bizhen-zhang/" + action;
}


