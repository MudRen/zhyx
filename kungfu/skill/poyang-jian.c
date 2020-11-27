inherit SKILL;

mapping *action = ({
([      "action":"$Nʹһʽ���������¡�������$w�������Һ�ɨ����$n��$l",
        "force" : 130,
        "parry" : 30,
        "dodge" : 50,
	    "attack": 100,
        "damage": 100,
        "lvl"   : 0,
        "skill_name" : "��������",
        "damage_type":  "����"
]),
([      "action":"$N̤��һ����������ʽ��������$w���������һ���������$n��$l",
        "force" : 150,
        "parry" : 40,
        "dodge" : 60,
	 "attack": 110,
        "damage": 110,
        "lvl"   : 30,
        "skill_name" : "����ʽ",
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һ�С��콵ʽ����бб�����ó�������$n��$l",
        "force" : 170,
        "parry" : 50,
        "dodge" : 70,
	 "attack": 120,
        "damage": 120,
        "lvl"   : 50,
        "skill_name" : "�콵ʽ",
        "damage_type":  "����"
]),
([      "action":"$N����$w����������Ȧ��һʽ��������졹��һ�������$n��$l",
        "force" : 190,
        "parry" : 60,
        "dodge" : 80,
        "damage": 130,
	 "attack": 130,
        "lvl"   : 70,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬һʽ�����ʽ������׼$n��$lбб����",
        "force" : 220,
        "parry" : 70,
        "dodge" : 90,
        "damage": 140,
	    "attack": 140,
        "lvl"   : 90,
        "skill_name" : "���ʽ",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ��������ʡ���$w��ն�������缲�������$n���ؿ�",
        "force" : 250,
        "parry" : 80,
        "dodge" : 100,
	    "attack": 150,
        "damage": 150,
        "lvl"   : 110,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һʽ���ƹ�ʽ����������Ϣ�ػ���$n��$l",
        "force" : 270,
        "parry" : 90,
        "dodge" : 110,
        "damage": 160,
	    "attack": 160,
        "lvl"   : 130,
        "skill_name" : "�ƹ�ʽ",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬��â���£�һʽ���������ʽ������׼$n��$lбб����",
        "force" : 300,
        "parry" : 100,
        "dodge" : 120,
        "damage": 170,
	    "attack": 170,
        "lvl"   : 150,
        "skill_name" : "�������ʽ",
        "damage_type":  "����"
]),
([      "action":"$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ�������ݺ᡹����$n���ʺ�",
        "force" : 310,
        "parry" : 110,
        "dodge" : 130,
	     "attack": 180,
        "damage": 180,
        "lvl"   : 170,
        "skill_name" : "�����ݺ�",
        "damage_type":  "����"
]),
([      "action":"$N���Ƶ�����һʽ�������޼�����$w�Ի���Ծ�����缲�������$n���ؿ�",
        "force" : 350,
        "parry" : 120,
        "dodge" : 140,
        "damage": 200,
	    "attack": 200,
        "lvl"   : 290,
        "skill_name" : "�����޼�",
        "damage_type":  "����"
])
});

int valid_enable(string usage)
{ 
       return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;
        int lv = me->query_skill("poyang-jian", 1);

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ѧϰ������⽣��\n");

        if (me->query("max_neili") < 1500)
                return notify_fail("���������Ϊ����������ѧϰ������⽣��\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򲻹�������ѧϰ������⽣��\n");

        if ((int)me->query_skill("sword", 1) < lv)
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������������⽣��\n");
       
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
        level = (int) me->query_skill("poyang-jian", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("�������������������⽣��\n");

        if ((int)me->query("neili") < 130)
                return notify_fail("�������������������⽣��\n");

        me->receive_damage("qi", 75);
        me->add("neili", -70);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poyang-jian/" + action;
}