//fengyun-bianhuan.c ���Ʊ��
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"ֻ��$N�Ų���ò���������һ���ٻΣ�һ�С��޿ײ��롹��˫ȭ����$n֮���أ�ʹ��$n$l��",
        "force" :100,
        "attack":12,
        "dodge" :30,
        "damage":12,
        "lvl"   :0,
        "skill_name" :"�޿ײ���",
        "damage_type":"����"
]),
([      "action":"$N����������˫�ȱ��ƶ��ڵ���һ�㣬һʽ���İ����ơ�������������ֱȭһ������$n$l��",
        "force" :130,
        "attack":20,
        "dodge" :60,
        "damage":26,
        "lvl"   :40,
        "skill_name" :"�İ�����",
        "damage_type":"����"
]),
([      "action":"$Nһ����Ծ������ʹ��һ�С���������衹����ȭ�����ͻ�$n��ͷ����",
        "force" :150,
        "attack":32,
        "dodge" :80,
        "damage":40,
        "lvl"   :70,
        "skill_name" :"���������",
        "damage_type":"����"
]),
([      "action":"$N˫��ƽ����ǰ��ʹ��һ�С�������ԯ������ǰ�����Ƴ�������$n��$l��",
        "force" :180,
        "attack":46,
        "dodge" :110,
        "damage":52,
        "lvl"   :100,
        "skill_name" :"������ԯ",
        "damage_type":"����"
]),
([      "action":"$N����΢ȭ��̽������ʹ��һ�С��ƴ����¡������ֺ������ⲿ���ص�ײ��$n$l��",
        "force" :220,
        "attack":65,
        "dodge" :150,
        "damage":68,
        "lvl"   :150,
        "skill_name" :"�ƴ�����",
        "damage_type":"����"
]),
([      "action":"$Nʹ����̫��ҹ�̡������²����ܶ�����������ǰ���棬��ȭ����$n$l��",
        "force" :250,
        "attack":78,
        "dodge" :180,
        "damage":80,
        "lvl"   :180,
        "skill_name" :"̫��ҹ��",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
         return notify_fail("�����Ʊ�ñ�����֡�\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ���Ʊ�á�\n");

     if ((int)me->query_skill("cuff", 1) < 100)
         return notify_fail("��Ļ���ȭ����򲻹���\n");

     if ((int)me->query("max_neili") < 350)
         return notify_fail("�������̫�ͣ��޷�ѧ���Ʊ�á�\n");

     if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("fengyun-bianhuan", 1))
         return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷���������ķ��Ʊ�á�\n");

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
     level = (int) me->query_skill("fengyun-bianhuan", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
         return notify_fail("�����Ʊ�ñ�����֡�\n");

     if ((int)me->query("qi") < 100)
            return notify_fail("����������������Ʊ�á�\n");

     if ((int)me->query("neili") < 90)
            return notify_fail("����������������Ʊ�á�\n");

     me->receive_damage("qi", 85);
     me->add("neili", -65);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"fengyun-bianhuan/" + action;
}

