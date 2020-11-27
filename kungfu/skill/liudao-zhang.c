// liudao-zhang �����ȷ�
// By Alf, Last Update 2001.10

// ���ǵ����������ǻ���������ҵ��������塡�˽��̡�������� 

inherit SKILL;

mapping *action = ({
([  "action": "$Nʹ��һ�С����ǵ�����������$w�󿪴��أ�ֱ��$n��$l�Ļ�ȥ",
        "force" : 100,
        "dodge": -5,
        "damage": 40,
        "lvl" : 10,
        "damage_type": "����"
]),
([      "action": "$N����$w��ɨ������������죬һ�С������ǻ�����$n��$l��ȥ",
        "force" : 110,
        "dodge": -5,
        "damage": 50,
        "lvl" : 20,
        "damage_type": "����"
]),
([      "action": "$N����$w�߾ٹ������Ӹ�����ʹһ�С�������ҵ��������$n��$l",
        "force" : 120,
        "dodge": -10,
        "damage": 60,
        "lvl" : 30,
        "damage_type": "����"
]),
([      "action": "$N����������һ�С�������塹չ��������$wЮ��������$n��$l",
        "force" : 130,
        "dodge": -10,
        "damage": 70,
        "lvl" : 40,
        "damage_type": "����"
]),
([      "action": "$Nʹ�����˽��̡�������$wȥ�Ʊ�ò�������$n��$l������ס",
        "force" : 140,
        "dodge": -20,
        "damage": 80,
        "lvl" : 50,
        "damage_type": "����"
]),
([      "action": "$N���β���������$w���ӣ�һ�С��������������������$n��$l",
        "force" : 150,
        "dodge": -20,
        "damage": 100,
        "lvl" : 60,
        "damage_type": "����"
]),
});

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("liudao-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("������������������ȷ���\n");
        me->receive_damage("qi", 25);
        return 1;
}

string perform_action_file(string action)
{
    return "/kungfu/skill/liudao-zhang/" + action;
}

