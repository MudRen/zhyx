inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([      "action": "�ں��������У�$N����һԾ��˫���繳��ꫣ�����$n��$l", 
        "force" : 60, 
        "dodge" : 20, 
        "parry" : 35, 
        "damage": 35, 
        "damage_type" : "ץ��" 
]), 
([      "action": "$N˫��ƽ����ǰ�����ֻ�ס���ţ�������Ȼץ��$n��$l", 
        "force" : 137, 
        "dodge" : 41, 
        "parry" : 21, 
        "damage": 40, 
        "damage_type" : "ץ��" 
]), 
([      "action": "$N�ͺ�һ����˫�ֻ���Ϊצ��һǰһ��ץ��$n��$l", 
        "force" : 143, 
        "dodge" : 49, 
        "parry" : 22, 
        "damage": 90, 
        "damage_type" : "ץ��" 
]), 
([      "action": "$N��ǰһ����˫צ����������׼$n��$l����ץ��", 
        "force" : 151, 
        "dodge" : 58, 
        "parry" : 38, 
        "damage": 150, 
        "damage_type" : "ץ��" 
]) 
}); 
 
int valid_learn(object me) 
{ 
        if ( me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("���������ֱ�����֡�\n"); 
         
        if ( me->query_skill("hand", 1) < 80) 
               return notify_fail("��Ļ����ַ�������\n");                 
 
        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qinlong-shou", 1)) 
                return notify_fail("��Ļ����ַ�����㣬�޷���������������֡�\n");        
 
        return 1; 
} 
         
int valid_enable(string usage) 
{ 
        return usage == "hand" || usage=="parry"; 
} 
 
int practice_skill(object me) 
{ 
        if( (int)me->query("qi") < 100 ) 
                return notify_fail("����������������Ϣһ�������ɡ�\n"); 
 
        if( (int)me->query("neili") < 80 ) 
                return notify_fail("������������ˡ�\n"); 
 
        me->receive_damage("qi", 80); 
        me->add("neili", -50); 
 
        return 1; 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"qinlong-shou/" + action; 
} 

