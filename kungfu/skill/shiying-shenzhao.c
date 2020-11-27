//shiying-shenzhao.c ߱ӥ��צ
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N������$n$l����������һ�С�ӥצ׽ʳ����צ����ͬһ��λץ����",
        "force" :100,
        "attack":12,
        "dodge" :40,
        "damage":15,
        "lvl"   :0,
        "skill_name" :"ӥצ׽ʳ",
        "damage_type":"ץ��"
]),
([      "action":"$N����������һ�С�����ӥ����˫�ֱ�$n��ͷ����ȥ��",
        "force" :120,
        "attack":20,
        "dodge" :60,
        "damage":26,
        "lvl"   :20,
        "skill_name" :"����ӥ����",
        "damage_type":"ץ��"
]),
([      "action":"$N�����ڹ���һ�С�ǧ���ٿס��������ڿն���˫צ����$n����ץȥ��",
        "force" :150,
        "attack":35,
        "dodge" :70,
        "damage":40,
        "lvl"   :50,
        "skill_name" :"ǧ���ٿ�",
        "damage_type":"ץ��"
]),
([      "action":"$Nһ�С�������ӥ��������Խ��б�����ң�����������ָ���ɿ��ץ��$nͷ����",
        "force" :180,
        "attack":50,
        "dodge" :85,
        "damage":45,
        "lvl"   :80,
        "skill_name" :"������ӥ",
        "damage_type":"ץ��"
]),
([      "action":"����$Nһ����߳��һ�С��������ߡ������ֻ��˸��뻡�����������ץ��$n��$l��",
        "force" :200,
        "attack":75,
        "dodge" :100,
        "damage":60,
        "lvl"   :150,
        "skill_name" :"��������",
        "damage_type":"ץ��"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
         return notify_fail("��߱ӥ��צ������֡�\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ߱ӥ��צ��\n");

     if ((int)me->query_skill("claw", 1) < 100)
         return notify_fail("��Ļ���צ����򲻹���\n");

     if ((int)me->query("max_neili") < 350)
         return notify_fail("�������̫�ͣ��޷�ѧ߱ӥ��צ��\n");

     if ((int)me->query_skill("claw", 1) < (int)me->query_skill("shiying-shenzhao", 1))
         return notify_fail("��Ļ���צ��ˮƽ���ޣ��޷����������߱ӥ��צ��\n");

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
     level = (int) me->query_skill("shiying-shenzhao", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if (me->query_temp("weapon") ||
         me->query_temp("secondary_weapon"))
            return notify_fail("��߱ӥ��צ������֡�\n");

     if ((int)me->query("qi") < 70)
            return notify_fail("�������������߱ӥ��צ��\n");

     if ((int)me->query("neili") < 80)
            return notify_fail("�������������߱ӥ��צ��\n");

     me->receive_damage("qi", 65);
     me->add("neili", -68);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"shiying-shenzhao/" + action;
}

