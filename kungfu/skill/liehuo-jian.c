inherit SKILL;

mapping *action = ({
([      "action": "$N����һ��������$w�������ѣ�ֱ��$nϯ���ȥ����������",
        "force" : 50,
        "attack": 70,
        "dodge" : 30,
        "damage": 30,
        "parry" : 70,
        "lvl"   : 0,
        "damage_type": "����"
]),
([      "action": "ͻȻ֮�䣬$N���������$wƾ������һ��������״����Ȼ��$n���ϻ�ȥ",
        "force" : 70,
        "attack": 80,
        "dodge" : 33,
        "parry" : 79,
        "damage": 38,
        "lvl"   : 40,
        "damage_type": "����"
]),
([      "action": "$N����ֱ�������ֳ�$w��$n�ɴ̹�ȥ����������������������",
        "force" : 90,
        "attack": 90,
        "dodge" : 41,
        "parry" : 85,
        "damage": 52,
        "lvl"   : 80,
        "damage_type": "����"
]),
([      "action": "$N���ҿ��һ���������Ǳ�$wȴ�����ɨ���д������˵������޿ײ���ĳ�$nϯ���ȥ",
        "force" : 110,
        "attack": 95,
        "dodge" : 45,
        "parry" : 92,
        "damage": 60,
        "lvl"   : 120,
        "damage_type": "����"
]),
([      "action": "$N������˵��������·��ͬʱ����$n��ͷ���ء�����$n���ż䣬�ָо����������������",
        "force" : 150,
        "attack": 97,
        "dodge" : 47,
        "parry" : 99,
        "damage": 72,
        "lvl"   : 160,
        "damage_type": "����"
]),
([      "action": "$N�����������$w�϶�Ϊһ��״��һ������ȼ�յĻ���ֱ��$n���˶�ֹ",
        "force" : 200,
        "attack": 100,
        "dodge" : 50,
        "parry" : 100,
        "damage": 100,
        "lvl"   : 180,
        "damage_type": "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ�һ𽣷���\n");

        if (me->query_skill("force", 1) < me->query_skill("liehuo-jian", 1))
                return notify_fail("����ڹ����ӻ��������޷�����������һ𽣷���\n");

        if (me->query_skill("sword", 1) < me->query_skill("liehuo-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������һ𽣷���\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("liehuo-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) || 
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("��������������һ𽣷���\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("��������������һ𽣷���\n");

        me->receive_damage("qi", 30);
        me->add("neili", -20);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liehuo-jian/" + action;
}


