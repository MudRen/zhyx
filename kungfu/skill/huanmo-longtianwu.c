// huanmo-longtianwu.c ��ħ������

inherit SKILL;

mapping *action = ({
([      "action":"$N����΢�֣�����һ�죬����$n��$l��",
        "force" :10,
        "dodge" :10,
        "damage":10,
        "lvl"   :0,
        "damage_type" :"����"
]),
([      "action":"$Nٿ��һ��ת��˫��һ����ֱ��$n��򢡣",
        "force" :20,
        "dodge" :15,
        "damage":20,
        "lvl"   :10,
        "damage_type" :"����"
]),
([      "action":"$N����һ�ݣ�˫�ֻ����쳣��׼$n�ĺ���ץȥ��",
        "force" :35,
        "dodge" :30,
        "damage":30,
        "lvl"   :25,
        "damage_type" :"����"
]),
([      "action":"$N������Σ�����ƮƮ������$n$l",
        "force" :50,
        "dodge" :40,
        "damage":40,
        "lvl"   :40,
        "damage_type" :"����"
]),
([      "action":"$N����΢��������$n���˫�ֱ�צ��ֱϮ$n���ԡ�",
        "force" :70,
        "dodge" :60,
        "damage":55,
        "lvl"   :60,
        "damage_type" :"����"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) { return combo=="xuwu-piaomiao"; }

int valid_learn(object me)
{ 
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
        return notify_fail("����ħ�����������֡�\n"); 

    if ((int)me->query_skill("force", 1) < 60)
        return notify_fail("����ڹ���򲻹����޷�ѧ��ħ�����衣\n"); 

    if ((int)me->query("max_neili") < 250) 
        return notify_fail("�������̫�����޷�����ħ�����衣\n"); 

    if ((int)me->query_skill("hand", 1) < (int)me->query_skill("huanmo-longtianwu", 1)) 
        return notify_fail("��Ļ����ַ���򲻹����޷���������Ļ�ħ�����衣\n"); 

    return 1;
}

mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level = (int)me->query_skill("huanmo-longtianwu", 1);
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
             return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
    if ((int)me->query("qi") < 45) 
         return notify_fail("�������̫���ˡ�\n"); 

    if ((int)me->query("neili") < 35) 
         return notify_fail("�����������������ħ�����衹��\n"); 

    me->receive_damage("qi", 28); 
    me->add("neili", -20); 

    return 1; 
}

