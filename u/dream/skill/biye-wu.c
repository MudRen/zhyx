// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// biye-wu.c ��Ҷ�����

inherit SKILL;

string *action_msg = ({
        "$N˫��������ƮƮһʽ��Ҷ�䡹��������Ҷ����$n��$l��ȥ",
        "$N���Ϊ���ģ��ҽ�һ����˫�ֽ�����裬����Ҷ���ɣ����ǡ�Ҷ�衹����$n��$l����",
        "$N����߸�Ծ������������ǰ���ұ�΢����ʹһ�С�ҶƮ�㡹����$n��$l�����Ŵ�ȥ",
        "$N΢һ�˾���˫����¶��һʽ����Ҷ������$n�������¶�������������Ӱ֮��",
        "$N˫��ƽ̯�����ƻ��������磬��������ǰ�Ƴ���\n�Ʒ�����ƿ�����һ�С���֦��������֦������ֱ��$n���Ѷ�ȥ",
        "$NͻȻ���ƣ��ɸ�����ǰ�����Ƴ����Ʒ����Σ�һʽ��Ҷ�糱����һƬ����ֱ��$n",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����Ҷ����������֡�\n");
        if ((int)me->query_skill("biyun-xinfa", 1) < 30)
                return notify_fail("��ı����ķ���򲻹����޷�ѧ��Ҷ����衣\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷�����Ҷ����衣\n");
        return 1;
}

mapping query_action(object me, object weapon)
{        
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(100),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "attack": 60 + random(20),
                "damage_type":random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("���������������Ҷ����衣\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"biye-wu/" + action;
}

