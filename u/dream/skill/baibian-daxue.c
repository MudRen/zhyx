// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// baibian-daxue.c

inherit SKILL;

string *action_msg = ({
        "$Nһ�С�ָ�㽭ɽ��������$w������$n������Ѩ!",
        "$N��������һ�С�������������$w���������£���$n�׺�Ѩ��ȥ",
        "$N��ǰ����һ��������$wһ�Σ�����һ��ʹ������������������$n�ĵز�Ѩ",
        "$N���е�$w���Ҽ��Σ����һ�ι�â��ʹ����ǧ���򻯡����ź�������������$n������Ѩ",
        "$N����Ծ��һʽ��ǧ�߳����������������Ӱ��������ס$n",
        "$N�������У�$w�Ƴ������â���ӳ�����̨�۾�����һ�п�һ�еع���$n",
        "$Nʹ��һ�С�������·��ͦ���й�ֱ����$w���Ĳ�������;��Ȼת�����ϱ���޷�",
        "$N�������е�$wб�̣�һ�С���ɵ�����������$n��ǰ̴�д�Ѩ",
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 150)
                return notify_fail("�������������û�а취���ٱ��Ѩ����\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("����ڹ���򲻹���������ѧϰ�ٱ��Ѩ��!\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("baibian-daxue", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������İٱ��Ѩ�ȷ���\n");

        return 1;
}

mapping query_action(object me, object weapon)
{        
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "dodge" : 50 + random(10),
                "parry" : 50 + random(10),
                "damage": 120 + random(50),
                "attack": 50 + random(10),
                "damage_type": "����",
        ]);
          
}

int practice_skill(object me)
{       object ob;
        if( !(ob = me->query_temp("weapon")) ||
            (string)ob->query("skill_type") != "staff" )
                return notify_fail("���������һ�����Ȳ���ѧϰ�ٱ��Ѩ����\n");

        if( (int)me->query("qi") < 60)
                return notify_fail("�����������û�а취��ϰ�ٱ��Ѩ����\n");

        if( (int)me->query("neili") < 60)
                return notify_fail("�������������û�а취��ϰ�ٱ��Ѩ����\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__ "baibian-daxue/" + action;
}

