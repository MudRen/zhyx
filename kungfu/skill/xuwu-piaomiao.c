// xuwu-piaomiao.c �������ȭ

inherit SKILL;

mapping *action = ({
([      "action":"$N�����鰴����ȭ�»���ֱ��$n��$l��ȥ��",
        "force" :50,
        "parry" :8,
        "dodge" :10,
        "damage":5,
        "lvl"   :0,
        "damage_type" :"����"
]),
([      "action":"$N�󲽿�ǰ������ȭ������ȭ��$n��$l��ȥ��",
        "force" :55,
        "parry" :10,
        "dodge" :15,
        "damage":10,
        "lvl"   :15,
        "damage_type" :"����"
]),
([      "action":"$N��̤��������˫ȭ�ɻ�$nͷ�����ࡣ",
        "force" :65,
        "parry" :10,
        "dodge" :10,
        "damage":20,
        "lvl"   :25,
        "damage_type" :"����"
]),
([      "action":"$N��ȭ���䣬�ε�$n��󣬡������ػӳ�һȭ,����$n��$l��",
        "force" :80,
        "parry" :30,
        "dodge" :20,
        "damage":35,
        "lvl"   :40,
        "damage_type" :"����"
]),
([      "action":"$N����ಽ���ù�$n����ȭ����$n������",
        "force" :100,
        "parry" :40,
        "dodge" :30,
        "damage":40,
        "lvl"   :50,
        "damage_type" :"����"
]),
([      "action":"$N��ȭ����$n�ұۣ���ȭ��$n��ͷ������ȥ��",
        "force" :130,
        "parry" :30,
        "dodge" :20,
        "damage":50,
        "lvl"   :70,
        "damage_type" :"����"
]),
([      "action":"$N����һ�ݣ����嵹ת��˫ȭ��$n�Ժ������",
        "force" :170,
        "parry" :50,
        "dodge" :80,
        "damage":70,
        "lvl"   :80,
        "damage_type" :"����"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) { return combo=="huanmo-longtianwu"; }

int valid_learn(object me)
{ 
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
        return notify_fail("��������翱�����֡�\n"); 

    if ((int)me->query_skill("force", 1) < 50) 
        return notify_fail("����ڹ���򲻹����޷�ѧ������翡�\n"); 

    if ((int)me->query("max_neili") < 250) 
        return notify_fail("�������̫�����޷���������翡�\n"); 

    if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("xuwu-piaomiao", 1))
        return notify_fail("��Ļ���ȭ����򲻹����޷����������������翡�\n");

    return 1;
}

mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level = (int)me->query_skill("xuwu-piaomiao", 1);
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
             return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
    if ((int)me->query("qi") < 50) 
         return notify_fail("�������̫���ˡ�\n"); 

    if ((int)me->query("neili") < 40) 
         return notify_fail("���������������������翡���\n"); 

    me->receive_damage("qi", 30); 
    me->add("neili", -20); 

    return 1; 
}

