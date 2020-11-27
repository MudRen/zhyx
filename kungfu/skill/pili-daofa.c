//pili-daofa.c ��������
//By haiyan

inherit SKILL;

mapping *action = ({
([      "action" : "$N����һ����������$w��һ�С����������������ź���������$n��$l��ȥ",
        "force"  : 30,
        "attack" : 10,
        "dodge"  : 30,
        "parry"  : 20,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action":"$N�趯$w��ʹ�����˷����꡹���ó�������$w��$n��ȥ��",
        "force" :45,
        "attack":22,
        "dodge" :40,
        "parry" :32,
        "damage":28,
        "lvl"   :20,
        "skill_name" :"�˷�����",
        "damage_type":"����"
]),
([      "action":"$N���һ����һ�С��������𡹣��Ӷ�$w���ٻ���$n$l��",
        "force" :60,
        "attack":34,
        "dodge" :53,
        "parry" :40,
        "damage":35,
        "lvl"   :50,
        "skill_name" :"��������",
        "damage_type":"����"
]),
([      "action":"$N�������ϣ�һ�ǡ����¸�������$wֱ��$n˫�ȡ�",
        "force" :80,
        "attack":50,
        "dodge" :70,
        "parry" :55,
        "damage":50,
        "lvl"   :90,
        "skill_name" :"���¸���",
        "damage_type":"����"
]),
([      "action":"$Nһ�С�б����Ӱ��������һԾ��б����ǰ�����ֻӶ�$w����ֱն$n��$l��",
        "force" :100,
        "attack":65,
        "dodge" :82,
        "parry" :68,
        "damage":65,
        "lvl"   :110,
        "skill_name" :"б����Ӱ",
        "damage_type":"����"
]),
([      "action":"ֻ��$N������ǰ��˫�ֽ���$w��һ�С����չ�������ٻ���$n��$l��",
        "force" :150,
        "attack":80,
        "dodge" :95,
        "parry" :80,
        "damage":80,
        "lvl"   :150,
        "skill_name" :"���չ��",
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
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ����������\n");

     if ((int)me->query_skill("blade", 1) < 80)
         return notify_fail("��Ļ���������򲻹���\n");

     if ((int)me->query("max_neili") < 300)
         return notify_fail("�������̫�ͣ��޷�ѧ����������\n");

     if ((int)me->query_skill("blade", 1) < (int)me->query_skill("pili-daofa", 1))
         return notify_fail("��ĵ���ˮƽ���ޣ��޷��������������������\n");

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
     level = (int) me->query_skill("pili-daofa",1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "blade")
            return notify_fail("��ʹ�õ��������ԡ�\n");

     if ((int)me->query("qi") < 70)
            return notify_fail("�����������������������\n");

     if ((int)me->query("neili") < 80)
            return notify_fail("�����������������������\n");

     me->receive_damage("qi", 65);
     me->add("neili", -68);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"pili-daofa/" + action;
}

