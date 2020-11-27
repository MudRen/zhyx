// This program is a part of NITAN MudLIB
// tangmen-throwing.c

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ��ķ���򲻹����޷�ѧ���Ű�����\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("����Ṧ��򲻹����޷��������Ű�����\n");

        if ((int)me->query("dex") < 30)
                return notify_fail("������������ɣ��޷�ѧϰ���Ű�����\n");

        if ((int)me->query("str") < 30)
                return notify_fail("��ı����������޷�ѧϰ���Ű�����\n");

        if ((int)me->query("int") < 28)
                return notify_fail("������Բ������޷�ѧϰ���Ű�����\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("tangmen-throwing", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ�����������������Ű�����\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("����������������Ű�����\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tangmen-throwing/" + action;
}

