// liumang-shenquan.c ��å��ȭ
// By Alf, Last Update 2001.11

// �ڻ����� ˫���� Ҷ��͵�� ������ɽ ���ɵ�ɽ �β�Ѱ�� �ͻ�����

inherit SKILL;

mapping *action = ({
([      "action" : "$N����������ȭ������ȭֱ����һ�С��ڻ����ġ���Ю�ŷ�������$n��$l",
        "force" : 120,
        "dodge" : 20,
        "parry" : 20,
        "lvl" : 0,
        "skill_name" : "�ڻ�����",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����˫ȭ�����տ�����ǰ����������һ�С�˫���������ϻ�$n��$l",
        "force" : 140,
        "dodge" : 15,
        "parry" : 15,
        "lvl" : 20,
        "skill_name" : "˫����",
        "damage_type" : "����"
]),
([      "action" : "$N����һ������ȭ���$n���ţ�����һ����Ҷ��͵�ҡ�����׼$n��$l����һץ",
        "force" : 160,
        "dodge" : 10,
        "parry" : 10,
        "lvl" : 40,
        "skill_name" : "Ҷ��͵��",
        "damage_type" : "����",
]),
([      "action" : "$N����һ����һ�С�������ɽ��������һ��ȥ����죬��ͷ��$n��$l������ȥ",
        "force" : 180,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "������ɽ",
        "damage_type" : "����"
]),
([      "action" : "$N����ֱͦ������ǰ�������˫��һ��ʹ��һ�С����ɵ�ɽ��������$n��$l",
        "force" : 200,
        "dodge" : -5,
        "parry" : -5,
        "lvl" : 80,
        "skill_name" : "���ɵ�ɽ",
        "damage_type" : "����"
]),
([      "action" : "$N����һ����һ�С��β�Ѱ�ߡ�������һ��ɨ���Ⱥ�ɨ��ͬʱ��ȭ����$n��$l",
         "force" : 210,
        "dodge" : -5,
        "parry" : -10,
        "lvl" : 90,
        "skill_name" : "�β�Ѱ��",
        "damage_type" : "����"
]),
([      "action" : "$N����һ���ֺ�˫ȭ���գ�״�绢צ��һ�С��ͻ�����������׼$n��$lץȥ",
         "force" : 220,
        "dodge" : -10,
        "parry" : -10,
        "lvl" : 100,
        "skill_name" : "�ͻ�����",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����å��ȭ������֡�\n");

        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�ͣ��޷�����å��ȭ��\n");

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
        level = (int) me->query_skill("liumang-shenquan",1);
        
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) 
                return action[NewRandom(i, 20, level/5)];
                    
}

int practice_skill(object me)
{
        int lvl = me->query_skill("liumang-shenquan", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
        
        me->receive_damage("qi", 30);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liumang-shenquan/" + action;
}


