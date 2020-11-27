// fuqi-daofa.c�����޵���
// By Alf, Last Update 2001.05

//��Ůò�ɲ����������������Ϊ��������������˫��������������̨
//��������ӳ��ȸ����������ױ�ɽ��ݡ�ϲ��˿������ľ��ǧ��һ��������

inherit SKILL;

mapping *action = ({
([  "action" : "$N����һЦ������$wбָ��һ�С�Ůò�ɲ�������������������$n��$l",
    "force" : 120,
    "dodge" : -10,
    "lvl" : 0,
    "skill_name" : "Ůò�ɲ�������",
    "damage_type" : "����"
]),
([  "action" : "$N���΢Ц��һ�С��������Ϊ��������$wһ��һ�գ�ƽ�л���$n�ľ���",
    "force" : 130,
    "dodge" : -10,
    "damage" : 5,
    "lvl" : 8,
    "skill_name" : "�������Ϊ����",
    "damage_type" : "����"
]),
([  "action" : "$Nչ��΢Ц��$w�������ҿ��أ�һ�С���������˫���������ն��$n",
    "force" : 140,
    "dodge" : -5,
    "damage" : 15,
    "lvl" : 16,
    "skill_name" : "��������˫����",
    "damage_type" : "����"
]),
([  "action" : "$Nʹһ�С������������̨����$w���϶��»���һ���󻡣���ֱ����$n",
    "force" : 160,
    "dodge" : 5,
    "damage" : 25,
    "lvl" : 24,
    "skill_name" : "�����������̨",
    "damage_type" : "����"
]),
([  "action" : "$N����$wһ����һ�С�������ӳ��ȸ������˫�ֳ��з��У�����$n�ؿ�",
    "force" : 180,
    "dodge" : 10,
    "damage" : 30,
    "lvl" : 33,
    "skill_name" : "������ӳ��ȸ��",
    "damage_type" : "����"
]),
([  "action" : "$Nһ�С�������ױ�ɽ��ݡ�������$w�������ã����ҿ�����������$n",
    "force" : 210,
    "dodge" : 15,
    "damage" : 35,
    "lvl" : 42,
    "skill_name" : "������ױ�ɽ���",
    "damage_type" : "����"
]),
([  "action" : "$NԾ����أ�$w˳���ͳ���һ�С�ϲ��˿������ľ����бб����$n��$l",
    "force" : 240,
    "dodge" : 5,
    "damage" : 50,
    "lvl" : 51,
    "skill_name" : "ϲ��˿������ľ",
    "damage_type" : "����"
]),
([  "action" : "$N��Ц���У���ǧ��һ����������ʹ����һƬ�����ĵ�Ӱӿ��$nȫ��",
    "force" : 280,
    "dodge" : 20,
    "damage" : 60,
    "lvl" : 60,
    "skill_name" : "ǧ��һ��������",
    "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
    if(level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("fuqi-daofa",1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "blade")
      return notify_fail("��ʹ�õ��������ԡ�\n");
    if ((int)me->query("qi") < 50)
      return notify_fail("����������������޵�����\n");
    me->receive_damage("qi", 25);
    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fuqi-daofa/" + action;
}


