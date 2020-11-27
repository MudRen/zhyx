// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// duoluoye-zhi.c - ���ֶ���Ҷָ(��Ϊ�Ե����书)
       
inherit SHAOLIN_SKILL;
        
string *action_msg = ({
        "$N����ǰ�㣬��ָ����һ�ž��磬Ʈ�����εĻ���$n��$l",
        "$N���󲻶���ӡ������Ծ��˫�ֻ�������$n������ָ��֮��",
        "$N������ϣ���ָ����ֱ�룬�ڵ�$n�Ĵ�Ѩ��һ�����ܾ��˵Ĵ�",
        "$N����Ծ�𣬾Ӹ����£�˫�ֱַ����$n�ĸ���ҪѨ",
        "$N��������ע��ָ�䣬һָ�������²��ɵ���Ӳ����$n�������У�����$n��$l",
        "$N�粽��ǰ��ͻȻ������ָ������һ���ǳɣ��������ָ�����$n",
        "$N������ϣ�����ʳָ�������������$n��$l���ƺ���������",
        "$N������ǰ������ȫ������˫ָ��������ָ�磬��$n��ȫ�����ڹ���֮��",
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
      
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("������Ҷָ������֡�\n"); 
      
        if ((int)me->query_skill("force") < 150) 
                return notify_fail("����ڹ���򲻹����޷�ѧϰ����Ҷָ��\n"); 
     
        if ((int)me->query("max_neili") < 2000) 
                return notify_fail("�������̫�����޷�������Ҷָ��\n"); 
      
        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("duoluoye-zhi", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ķ���Ҷָ��\n"); 
      
        return 1; 
} 
      
mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 360 + random(120),
                "attack": 80 + random(10),
                "dodge" : 80 + random(10),
                "parry" : 80 + random(10),
                "damage_type" : "����",
        ]);        
}

int practice_skill(object me) 
{ 
        if (me->query_temp("weapon") || 
            me->query_temp("secondary_weapon")) 
                return notify_fail("����������ϰ��\n"); 
      
        if ((int)me->query("qi") < 90) 
                return notify_fail("�������̫���ˡ�\n"); 
      
        if ((int)me->query("neili") < 90) 
                return notify_fail("�����������������Ҷָ��\n");
      
        me->receive_damage("qi", 80);
        me->add("neili", -80); 
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"duoluoye-zhi/" + action; 
}
