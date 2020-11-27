//tianmo-zhang.c ��ħ�Ʒ�
//By haiyan

inherit SKILL; 

mapping *action =({
([      "action":"$N���һ�գ�����������б������ʹ��һ�С���ħ��������һ������$n��$l��",
        "force" :40,
        "attack":15,
        "parry" :30,
        "dodge" :30,
        "damage":18,
        "lvl"   :0,
        "skill_name" :"��ħ����",
        "damage_type":"����"
]),
([      "action":"$Nһ�����������Ӽ��Σ�ʹ��һ�С�����Ӱ�����ó�������Ӱ������$nȫ��ĸ���ҪѨ��",
        "force" :60,
        "attack":25,
        "parry" :50,
        "dodge" :60,
        "damage":20,
        "lvl"   :50,
        "skill_name" :"����Ӱ",
        "damage_type":"����"
]),
([      "action":"$N���һ�����ҿ�һ����˲������$n����ǰ��һ�С�ħ���ɲ����˫����������������$n��",
        "force" :80,
        "attack":38,
        "parry" :80,
        "dodge" :70,
        "damage":32,
        "lvl"   :80,
        "skill_name" :"ħ���ɲ",
        "damage_type":"����"
]),
([      "action":"$Nʹһ�С�����·����������ǰ����˫�Ƹ����˸���Բ����������$n��$l��",
        "force" :100,
        "attack":45,
        "parry" :90,
        "dodge" :90,
        "damage":46,
        "lvl"   :100,
        "skill_name" :"����·��",
        "damage_type":"����"
]),
([      "action":"$Nʹ��һ�С���ľ�������������������ƣ�ǣ��ȫ����$n�����˻���",
        "force" :120,
        "attack":62,
        "parry" :100,
        "dodge" :110,
        "damage":60,
        "lvl"   :120,
        "skill_name" :"��ľ����",
        "damage_type":"����"
]),
([      "action":"$N����һ�ڣ���Ȼ�������ߣ�����˳��һ�С�ħӰ���ء���$n��$l��ȥ��",
        "force" :150,
        "attack":80,
        "parry" :120,
        "dodge" :140,
        "damage":75,
        "lvl"   :150,
        "skill_name" :"ħӰ����",
        "damage_type":"����"
]),
([      "action":"$Nʹ��������ʵӦ�������������������ɺ���ϣ��γ�һ����������$n",
        "force" :180,
        "attack":100,
        "parry" :150,
        "dodge" :160,
        "damage":100,
        "lvl"   :180,
        "skill_name" :"����ʵӦ",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
         return notify_fail("����ħ�Ʒ�������֡�\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ��ħ�Ʒ���\n");

     if ((int)me->query_skill("strike", 1) < 80)
         return notify_fail("��Ļ����Ʒ���򲻹���\n");

     if ((int)me->query("max_neili") < 300)
         return notify_fail("�������̫�ͣ��޷�ѧ��ħ�Ʒ���\n");

     if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tianmo-zhang", 1))
         return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������ħ�Ʒ���\n");

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
     level = (int) me->query_skill("tianmo-zhang", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
         return notify_fail("����ħ�Ʒ�������֡�\n");

     if ((int)me->query("qi") < 80)
            return notify_fail("���������������ħ�Ʒ���\n");

     if ((int)me->query("neili") < 70)
            return notify_fail("���������������ħ�Ʒ���\n");

     me->receive_damage("qi", 65);
     me->add("neili", -55);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-zhang/" + action;
}

