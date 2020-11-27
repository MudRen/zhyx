//tianmo-jian.c ��ħ����
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N����$wһ�����û������콣Ӱ��һ�С����»Ի͡�ǡ�������ѩ����$n��",
        "force" :210,
        "attack":160,
        "dodge" :80,
        "parry" :110,
        "damage":150,
        "lvl"   :0,
        "skill_name" :"���»Ի�",
        "damage_type":"����"
]),
([      "action":"$N��ȻһЦ�����μ������·�ɵ�Ϸ��һ�㣬����$n���ߣ�����$wʹ��һ�С���̦���͡�������$n�̳��彣��",
        "force" :230,
        "attack":175,
        "dodge" :90,
        "parry" :150,
        "damage":190,
        "lvl"   :30,
        "skill_name" :"��̦����",
        "damage_type":"����"
]),
([      "action":"$N����ǰ������Ʈ�ݣ�������ӹ����գ�һ�С�����һ�ߡ����е�$w���һ��������$n��",
        "force" :250,
        "attack":190,
        "dodge" :110,
        "parry" :160,
        "damage":190,
        "lvl"   :80,
        "skill_name" :"����һ��",
        "damage_type":"����"
]),
([      "action":"$Nһ������$w��ʹ��һ�С�������졹ֻ��$N����������$w��$n��ȥ��һ�ɾ������š�ž��ž����������$n��ȥ��",
        "force" :280,
        "attack":210,
        "dodge" :120,
        "parry" :180,
        "damage":220,
        "lvl"   :110,
        "skill_name" :"�������",
        "damage_type":"����"
]),
([      "action":"$N�Ų����Ʋ�������ת����$w����������ֱ�����һʽ��΢����˫�ɡ����϶���ֱ��$n������",
        "force" :320,
        "attack":230,
        "dodge" :150,
        "parry" :200,
        "damage":190,
        "lvl"   :150,
        "skill_name" :"΢����˫��",
        "damage_type":"����"
]),
([      "action":"$N�ĵ׿������������⣬���а�Ȼ�������ǡ��մ���ͥ������$nΪ$N�������ƣ���ס���ˡ�",
        "force" :330,
        "attack":220,
        "dodge" :180,
        "parry" :220,
        "damage":210,
        "lvl"   :180,
        "skill_name" :"�մ���ͥ��",
        "damage_type":"����"
]),
([      "action":"ֻ��$N����$w��������֮����������ͣ�����������������һ�С�׳��������������ֱ��$n���̹�ȥ��",
        "force" :340,
        "attack":250,
        "dodge" :200,
        "parry" :210,
        "damage":220,
        "lvl"   :210,
        "skill_name" :"׳������",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "sword")
         return notify_fail("�����װ��������ѧϰ������\n");

     if ((int)me->query_skill("xixing-dafa", 1) < 150)
         return notify_fail("������Ǵ󷨻�δ��ɣ�����ѧϰ��ħ������\n");

     if ((int)me->query_skill("sword", 1) < 130)
         return notify_fail("��Ļ���������򲻹���\n");

     if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tianmo-jian", 1))
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
     level = (int) me->query_skill("tianmo-jian", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;
     int cost;

     if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "sword")
         return notify_fail("�����װ����������������\n");

     if ((int)me->query("qi") < 160)
         return notify_fail("�������̫���ˡ�\n");

     cost = me->query_skill("tianmo-jian", 1) / 2 + 100;
     if ((int)me->query("neili") < cost)
         return notify_fail("�����������������ħ��������\n");

     me->receive_damage("qi", 130);
     me->add("neili", -cost);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-jian/" + action;
}

