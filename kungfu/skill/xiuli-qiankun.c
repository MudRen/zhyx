//xiuli-qiankun.c 
         
inherit SHAOLIN_SKILL;  
         
mapping *action = ({  
([        "action" : "$Nһʽ��ͯ�Ӱݷ𡹣�˫��¡��һ���ޱ߰���ӿ��$n",  
        "force" : 200,  
        "dodge" : 5,  
        "parry" : 0, 
        "damage": 10,  
        "lvl" : 9,      
        "skill_name" : "ͯ�Ӱݷ�",      
        "damage_type" : "����"  
]), 
([        "action" : "$N����ͻת��˫����裬��ʱ���ĳ�ǧ�ٵ���Ӱ������һ�С�����Ʈ�졹����$n�޿ɶ��",       
        "force" : 230,  
        "dodge" : 15,  
        "parry" : 10,  
        "damage": 10,  
        "lvl" : 29,      
        "skill_name" : "����Ʈ��", 
        "damage_type" : "����"  
]), 
([        "action" : "$N˫��һ��һ�գ��ƾ�ȴ���¶���бб������һʽ���ط���������$n��Ҫ��ʱ��Ȼ����",  
        "force" : 270,  
        "dodge" : 5, 
        "parry" : 15, 
        "damage": 20,  
        "lvl" : 39,      
        "skill_name" : "�ط�����", 
        "damage_type" : "����"  
]), 
([        "action" : "ֻ��$N˫��һ�ڣ���Ȼ�������ߣ�����˳������һ�С��ҷ��˵�����$n��$l��ȥ", 
        "force" : 320,  
        "dodge" : 10, 
        "parry" : 5,  
        "damage": 15, 
        "lvl" : 49,      
        "skill_name" : "�ҷ��˵�",      
        "damage_type" : "����"  
]), 
([        "action" : "$N���ζ����������������׻ӳ���ӿ��$n��$l���������������һ�С�������ů��", 
        "force" : 380,  
        "dodge" : 25, 
        "parry" : -5, 
        "damage": 25, 
        "lvl" : 59,      
        "skill_name" : "������ů", 
        "damage_type" : "����"  
]), 
([        "action" : "$N����һ������������һ��һʽ����ɽ�ӡ���˫�Ƶ���ƽ�ƶ��������ƻ�����$nȴ���޷����ܣ�", 
        "force" : 420,  
        "dodge" : 15,  
        "parry" : 0,  
        "damage": 35, 
        "lvl" : 69,     
        "skill_name" : "��ɽ��",      
        "damage_type" : "����"  
]), 
([        "action" : "$N�͵��Ż��󿪣�ӭ��$n�����ƺ�����ϣ��ƾ������һ���ǣ�$NͻȻһ�����ӷ�������ʯ��$n��������Ȼȫ�����أ��������ֲ���֮�ܡ�Ǭ����ת��",  
        "force" : 480,  
        "dodge" : 20,  
        "parry" : 10,  
        "damage": 50,  
        "lvl" : 80,      
        "skill_name" : "Ǭ����ת",      
        "damage_type" : "����"  
])  

});  
int valid_enable(string usage) { return  usage=="unarmed" || usage=="parry"; }  
 
int valid_learn(object me)  
{  
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))      
                return notify_fail("������Ǭ������֡�\n");  
        if ((int)me->query_skill("shaolin-xinfa", 1) < 100)      
                return notify_fail("��������ķ��������޷�ѧϰ����Ǭ����\n");  
        if ((int)me->query("max_neili") < 1500)  
                return notify_fail("�������̫�����޷���ϰ����Ǭ����\n");  
        return 1;  
}  
mapping query_action(object me, object weapon)  
{  
        int     i, level;  
        level   = (int)me->query_skill("xiuli-qiankun",1);      
        for(i = sizeof(action); i >     0; i--)  
        if(level > action[i-1]["lvl"])  
        return action[NewRandom(i, 20, level/5)];  
}  
int practice_skill(object me)  
{ 
        if ((int)me->query("qi") < 30)  
                return notify_fail("�������̫���ˡ�\n");  
        if ((int)me->query("neili")     < 20)  
                return notify_fail("�������������ϰ����Ǭ����\n");  
        me->add("neili", -10);  
        return 1;
} 
string perform_action_file(string action)  
{  
        return __DIR__"xiuli-qiankun/" + action;  
} 

