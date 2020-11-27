// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// duanyun-fu.c ���Ƹ�

inherit SKILL;

string *action_msg = ({
        "$N����ڿ�Ծ��˫�ֽ���$w����׼$n��ͷ�������϶��µؿ�����ȥ��ֻ�ڰ��������һ�ž޴�ĺ�Ӱ",
        "$NͻȻ��һ��������ǰ����������$w���¶��Ϸ���$n����·��$n����һ������ɫ����Ӱ�����Լ�����֪�����æ�м�",
        "$N��Ȼ����һ��������б����ǰ�����һ��������΢�Σ�����$w�ڿ��л���һ����Ӱ�����ٺ�ɨ$n���Ҽ磬��������",
        "$NͻȻ�������ҹ������漴���𣬾��������һ˲�䣬�ѵ�������$w����$n�����ߣ����ּȿ��Һ�",
        "$N˫�ֺ��$w��ƽɨ$nǰ�أ���ʽδʹ�Ͼ��Ѵ�ס�Ȼ���У�����ֱײ$n��С����",
        "$N����������ת��΢�ף�$n��$N¶����������æ������ȴͻȻ����$N��������ת����������$w��Ѹ�͵�ɨ���Լ�������",
        "$N����΢��������ͬһʱ�������������ҿ����師��$n�����$w�Ӳ�ͬ�ķ�λ�����Լ���һʱ�侹��֪������м�",
        "$Nǰ���͵�������һ�٣����Ҳ΢΢һ�𣬽��ž���ͷ��ͷ����ת��Ȧ��$w����������֮��ƽֱ�����ȵ�Ϯ��$n��\n"
        "$n������δ����㣬�ܿ����������Լ�����һ�ߣ����ɴ�ʧɫ",
});

int valid_enable(string usage) { return usage == "axe" ||  usage == "parry"; }      

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("����ڹ��ķ���򲻹����޷�ѧ���Ƹ���\n");
        if ((int)me->query("max_neili") < 150)
                return notify_fail("�������̫�����޷������Ƹ���\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 260 + random(50), 
                "attack": 40 + random(10), 
                "dodge" : 40 + random(10), 
                "parry" : 40 + random(10), 
                "damage_type" : "����", 
        ]); 
}

int practice_skill(object me)
{
        object weapon;
    
        if (!objectp(weapon = me->query_temp("weapon"))
        ||  (string)weapon->query("skill_type") != "axe")
                return notify_fail("��ʹ�õ��������ԡ�\n");    

        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
                
        if ((int)me->query("neili") < 50)
                return notify_fail("����������������Ƹ���\n");
                
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duanyun-fu/" + action;
}


