// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yixing-bufa.c ���β���

inherit SKILL;

string *dodge_msg = ({
        "$n�������ĵ���������һ�����պñܹ�$N���������ơ�\n",
        "����$n����������������һ���������$N��һ�С�\n",
        "����$n����Ʈ��������һ�ݣ����ѱܿ���\n",
        "$n������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$n����һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n�㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
        "$n����΢�Σ��о����յرܿ���$N��һ�С�\n",
        "$n�������ĵ�����һ������ͷ΢��,�����ܹ���$N��һ�С�\n"
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("����������������β�����\n");
        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}



string perform_action_file(string action)
{
      return __DIR__"yixing-bufa/" + action;
}

