//tianmo-shou.c ��ħ��
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$Nһ�С����귭�ơ�������ץ��$n�ĵ������$n�����Է���һ˲�䣬����ȴ��������$n��$l��",
        "force" :95,
        "attack":15,
        "parry" :10,
        "dodge" :30,
        "damage":20,
        "lvl"   :0,
        "skill_name" :"���귭��",
        "damage_type":"����"
]),
([      "action":"$N˫��һ������������ƶ�����һ�С�������ӿ������һ�ɾ�������$n��$l��",
        "force" :120,
        "attack":28,
        "parry" :40,
        "dodge" :60,
        "damage":35,
        "lvl"   :50,
        "skill_name" :"������ӿ",
        "damage_type":"����"
]),
([      "action":"����$Nһ��ŭ�����ָ߸߾���һʽ����ɽ��ˮ��������$n��$l��",
        "force" :160,
        "attack":40,
        "parry" :70,
        "dodge" :90,
        "damage":53,
        "lvl"   :80,
        "skill_name" :"��ɽ��ˮ",
        "damage_type":"����"
]),
([      "action":"$N����΢б���漴���һ�������ֺ��ƺ�צʹ��������ãã��������$n��$l��",
        "force" :190,
        "attack":56,
        "parry" :100,
        "dodge" :120,
        "damage":70,
        "lvl"   :130,
        "skill_name" :"����ãã",
        "damage_type":"����"
]),
([      "action":"$Nʹ������û�粨���˫�ֻ����쳣��׼$n��$lץȥ��",
        "force" :220,
        "attack":74,
        "parry" :130,
        "dodge" :150,
        "damage":90,
        "lvl"   :160,
        "skill_name" :"��û�粨��",
        "damage_type":"ץ��"
]),
([      "action":"$N������$n$l���������һ�С�����׽Ӱ����������ͬһ��λץȥ��",
        "force" :260,
        "attack":100,
        "parry" :180,
        "dodge" :200,
        "damage":150,
        "lvl"   :200,
        "skill_name" :"����׽Ӱ",
        "damage_type":"ץ��"
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
         return notify_fail("����ħ�ֱ�����֡�\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ��ħ�֡�\n");

     if ((int)me->query_skill("hand", 1) < 100)
         return notify_fail("��Ļ����ַ���򲻹���\n");

     if ((int)me->query("max_neili") < 350)
         return notify_fail("�������̫�ͣ��޷�ѧ��ħ�֡�\n");

     if ((int)me->query_skill("hand", 1) < (int)me->query_skill("tianmo-shou", 1))
         return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷������������ħ�֡�\n");

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
     level = (int) me->query_skill("tianmo-shou", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
         return notify_fail("����ħ�ֱ�����֡�\n");

     if ((int)me->query("qi") < 100)
            return notify_fail("���������������ħ�֡�\n");

     if ((int)me->query("neili") < 90)
            return notify_fail("���������������ħ�֡�\n");

     me->receive_damage("qi", 85);
     me->add("neili", -65);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-shou/" + action;
}

