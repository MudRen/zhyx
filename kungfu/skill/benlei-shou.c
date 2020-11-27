// benlei-shou.c ������
// By Alf
//�׶����С�����է�֡��ױ����ܡ�������������Ұ���ס��׶����졡�׾����ơ��������

inherit SKILL;

mapping *action = ({
([      "action" : "$N���еͺȣ����Ƶ�������֮�ϣ�ʩչ�����׶����С�����Ȼ����$n",
        "force" : 130,
        "dodge" : 20,
        "damage" : 10,
        "lvl" : 0,
        "skill_name" : "�׶�����",
        "damage_type" : "����"
]),
([      "action" : "$N����������һ�С�����է�֡���˫����ƮƮ������$n��$l",
        "force" : 150,
        "dodge" : 10,
        "damage" : 30,
        "lvl" : 20,
        "skill_name" : "����է��",
        "damage_type" : "����"
]),
([      "action" : "$N��Ц������˫�Ʒ��ɣ��û����ƣ�һ�С��ױ����ܡ��ѽ�$n��������",
        "force" : 150,
        "dodge" : 30,
        "damage" : 35,
        "lvl" : 30,
        "skill_name" : "�ױ�����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ����߳��һʽ��������������˫��һǰһ��Ѹ������$n��$l",
        "force" : 250,
        "dodge" : 20,
        "damage" : 10,
        "lvl" : 40,
        "skill_name" : "��������",
        "damage_type" : "����"
]),

([      "action" : "$N�ͺ�һ����˫��ƽ�ӣ����ױ��а����$n������һ�С���Ұ���ס�",
        "force" : 300,
        "dodge" : 25,
        "damage" : 50,
        "lvl" : 60,
        "skill_name" : "��Ұ����",
            "damage_type" : "����"
]),
([      "action" : "$Nŭ��һ�������ζ�Ȼ����˫���»���һ�С��׶����졹����$n�Ķ���",
        "force" : 350,
        "dodge" : 30,
        "damage" : 80,
        "lvl" : 70,
        "skill_name" : "�׶�����",
        "damage_type" : "����"
]),
([      "action" : "$N��߳���У�������Σ�����һ�С��׾����ơ����ɻ�$n���ظ�֮��",
        "force" : 350,
        "dodge" : 30,
        "damage" : 90,
        "lvl" : 80,
        "skill_name" : "�׾�����",
           "damage_type" : "����"
]),
([      "action" : "$Nһ����Х��˫��Ю�磬�Ƽ����ң�ʩ�������������ͬʱ����$n��$l",
        "force" : 450,
        "dodge" : -10,
        "damage" : 120,
        "lvl" : 100,
        "skill_name" : "�������",
    "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������ֱ�����֡�\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷��������֡�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("benlei-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("������������������֡�\n");
        me->receive_damage("qi", 25);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"benlei-shou/" + action;
}

