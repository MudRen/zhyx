// wuxing-jueji.c ���о���

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ��ķ���򲻹����޷�ѧ���о�����\n");

        if ((int)me->query_skill("dodge") < 80)
                return notify_fail("����Ṧ��򲻹����޷��������о�����\n");

        if ((int)me->query_dex() < 26)
                return notify_fail("������������ɣ��޷��������о�����\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("wuxing-jueji", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ�����������������о�����\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("����������������о�����\n");

        me->receive_damage("qi", 52);
        me->add("neili", -35);
        return 1;
}
