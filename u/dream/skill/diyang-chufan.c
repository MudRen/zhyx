// dragon-strike.c ����ʮ���� ����ެ 

inherit SKILL; 

mapping *action = ({ 
([      "action" : "$Nʹ��������ެ����˫���������ϻ���$n��$l",     
        "dodge"  : 90, 
        "parry"  : 90, 
        "attack" : 90,
        "force"  : 190, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
}); 

string main_skill() { return "dragon-strike"; } 

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }   

int valid_learn(object me) 
{ 
       if (me->query_skill("dragon_strike", 1) > 0) 
               return notify_fail("���Ѿ�ѧȫʮ�����ˣ������ٵ���ѧϰ��\n"); 

       if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 

       if ((int)me->query("str") < 30) 
               return notify_fail("���������ӹǻ�������ʮ���ƣ�С��Ū���˸첲��\n"); 

       if ((int)me->query_skill("force") < 90) 
               return notify_fail("����ڹ���򲻹��޷�ѧϰ����ʮ���ơ�\n"); 

       if ((int)me->query("max_neili") < 600) 
               return notify_fail("�������̫���޷�ѧϰ����ʮ���ơ�\n"); 

       if ((int)me->query_skill("strike", 1) < 30) 
               return notify_fail("��Ļ����Ʒ���򲻹����޷�ѧϰ����ʮ���ơ�\n"); 

       if ((int)me->query_skill("strike", 1) < (int)me->query_skill("feilong-zaitian", 1)) 
               return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ���ʮ���ơ�\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
        return action[random(sizeof(action))]; 
} 

int practice_skill(object me)  
{ 
       if ((int)me->query("qi") < 110)  
               return notify_fail("�������̫���ˡ�\n"); 

       if ((int)me->query("neili") < 100) 
               return notify_fail("�����������������ʮ���ơ�\n"); 

       me->receive_damage("qi", 90); 
       me->add("neili", -80); 
       return 1; 
} 

string perFORM_action_file(string action) 
{ 
       return __DIR__"diyang-chufan/" + action; 
} 



