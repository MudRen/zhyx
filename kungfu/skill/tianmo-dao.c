//tianmo-dao.c ��ħ����
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N�߸�Ծ��һʽ������Ǭ��������$n$lһ����",
        "force" :60,
        "attack":18,
        "dodge" :30,
        "parry" :20,
        "damage":25,
        "lvl"   :0,
        "skill_name" :"����Ǭ��",
        "damage_type":"����"
]),
([      "action":"ֻ��$N����$w�����μ��壬������$n����֮�ʣ�ͻȻʹ����꼻�һ�֡���$n����б�����¡�",
        "force" :80,
        "attack":25,
        "dodge" :50,
        "parry" :35,
        "damage":30,
        "lvl"   :30,
        "skill_name" :"꼻�һ��",
        "damage_type":"����"
]),
([      "action":"$Nһʽ���Ǻ������졹������$w����һ������, �����ӵ�к�����$n$l��",
        "force" :95,
        "attack":38,
        "dodge" :70,
        "parry" :50,
        "damage":50,
        "lvl"   :60,
        "skill_name" :"�Ǻ�������",
        "damage_type":"����"
]),
([      "action":"$N�����㱣�����$wƮҡ������һ�С��߷�Ʈҡ��бб�Ŀ���$n��$l��",
        "force" :110,
        "attack":45,
        "dodge" :90,
        "parry" :75,
        "damage":70,
        "lvl"   :90,
        "skill_name" :"�߷�Ʈҡ",
        "damage_type":"����"
]),
([      "action":"$N���һ����ʹ��һ�С������ã����˫�ֽ���$w���ű��˵�ɱ��������$n��$l��",
        "force" :130,
        "attack":62,
        "dodge" :110,
        "parry" :95,
        "damage":85,
        "lvl"   :120,
        "skill_name" :"�����ã",
        "damage_type":"����"
]),
([      "action":"$Nб�����һ�С��˷����ˡ�������һƬ�������$n��$l��",
        "force" :160,
        "attack":80,
        "dodge" :110,
        "parry" :102,
        "damage":100,
        "lvl"   :150,
        "skill_name" :"�˷�����",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "blade")
         return notify_fail("������������ŵ�������������\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ��ħ������\n");

     if ((int)me->query_skill("blade", 1) < 100)
         return notify_fail("��Ļ���������򲻹���\n");

     if ((int)me->query("max_neili") < 350)
         return notify_fail("�������̫�ͣ��޷�ѧ��ħ������\n");

     if ((int)me->query_skill("blade", 1) < (int)me->query_skill("tianmo-dao", 1))
         return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������ħ������\n");

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
     level = (int) me->query_skill("tianmo-dao", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "blade")
         return notify_fail("������������ŵ���������ħ������\n");

     if ((int)me->query("qi") < 100)
            return notify_fail("���������������ħ������\n");

     if ((int)me->query("neili") < 90)
            return notify_fail("���������������ħ������\n");

     me->receive_damage("qi", 70);
     me->add("neili", -75);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-dao/" + action;
}

