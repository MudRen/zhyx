inherit SKILL;

mapping *action = ({
([      "action": "$Nһ�С���÷��Թ����˫�ֺ�ӣ�ץ��$n",
        "force" : 80,
        "attack": 125,
        "dodge" : 20,
        "parry" : 25,
        "damage": 110,
        "lvl"   : 0,
        "skill_name" : "��÷��Թ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С��ƻ���Գ������ԾȻ����ץ��$n��ͷ��",
        "force" : 100,
        "attack": 128,
        "dodge" : 20,
        "parry" : 27,
        "damage": 120,
        "lvl"   : 30,
        "skill_name" : "�ƻ���Գ�",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С���ɽһ�����ı̡���˫�ַ׷ɣ�$nֻ���ۻ�����",
        "force" : 120,
        "attack": 132,
        "dodge" : 30,
        "parry" : 28,
        "damage": 130,
        "lvl"   : 60,
        "skill_name" : "��ɽһ�����ı�",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С�÷��ѩ�串��ƻ����˫�ֺϻ���$nֻ���޴��ɱ�",
        "force" : 150,
        "attack": 133,
        "dodge" : 30,
        "parry" : 33,
        "damage": 135,
        "lvl"   : 80,
        "skill_name" : "÷��ѩ�串��ƻ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С�������÷��ѩ�ҡ���˫��ƮȻץ��$n",
        "force" : 180,
        "attack": 136,
        "dodge" : 30,
        "parry" : 37,
        "damage": 145,
        "lvl"   : 100,
        "skill_name" : "������÷��ѩ��",
        "damage_type" : "����"
]),

([      "action": "$N˫��ƽ�٣�һ�С�����������ŪӰ������$n",
        "force" : 210,
        "attack": 142,
        "dodge" : 135,
        "parry" : 45,
        "damage": 140,
        "lvl"   : 120,
        "skill_name" : "����������ŪӰ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С���������ֱ���ۡ�������$n���ƺ�$n��ȫ��������",
        "force" : 240,
        "attack": 147,
        "dodge" : 30,
        "parry" : 41,
        "damage": 145,
        "lvl"   : 140,
        "skill_name" : "��������ֱ����",
        "damage_type" : "����"
]),

([      "action": "$N������Σ�����һ�ǡ�����δ�϶��Ⱦ�������$n��ͷ��",
        "force" : 280,
        "attack": 146,
        "dodge" : 30,
        "parry" : 47,
        "damage": 150,
        "lvl"   : 160,
        "skill_name" : "����δ�϶��Ⱦ�",
        "damage_type" : "����"
]),
([      "action": "$Nʩ��������Ц�졹�����ֺ�ɨ$n��$l�����ֹ���$n���ؿ�",
        "force" : 330,
        "attack": 158,
        "dodge" : 110,
        "parry" : 155,
        "damage": 150,
        "lvl"   : 170,
        "skill_name" : "����Ц��",
        "damage_type" : "����"
]),
([      "action": "$Nʩ������ʯ��١�������һ������$n",
        "force" : 370,
        "attack": 162,
        "dodge" : 120,
        "parry" : 152,
        "damage": 180,
        "lvl"   : 180,
        "skill_name" : "��ʯ���",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="parry"|| usage=="hand"; }

int valid_combine(string combo) { return combo=="liuyang-zhang"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ң��÷�ֱ�����֡�\n");

        if (me->query("dex") < 30)
                return notify_fail("�����������㣬�޷�ѧϰ���ɵ���ң��÷�֡�\n");
          

        if ((int)me->query("max_neili") < 900)
                return notify_fail("�������̫�����޷�����ң��÷�֡�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷�����ң��÷�֡�\n");

        if ((int)me->query_skill("hand", 1) < 100)
                return notify_fail("��Ļ����ַ���򲻹����޷�����ң��÷�֡�\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("zhemei-shou", 1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷������������ң��÷�֡�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("zhemei-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 120)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("���������������ң��÷�֡�\n");

        me->receive_damage("qi", 350);
        me->add("neili", -350);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhemei-shou/" + action;
}
