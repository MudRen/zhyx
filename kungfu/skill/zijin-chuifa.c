// zijin-chuifa.c �Ͻ𴸷�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N˫��һ������$w�д������װ����������ͷ�����ؾ���$n���˹�ȥ��",
        "force"  : 100,
        "dodge"  : -3,
        "parry"  : 15,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type": "����"
]),
([      "action" : "ֻ��$N��ð�׹⣬���͹�𣬳���$w�ͳ�$n��$l����ɨȥ��",
        "force"  : 150,
        "dodge"  : -5,
        "parry"  : 20,
        "damage" : 30,
        "lvl"    : 20,
        "damage_type": "����"
]),
([      "action" : "$N���е�$w�������ᣬ�����転����$n$l������ȥ��",
        "force"  : 180,
        "dodge"  : -8,
        "parry"  : 20,
        "damage" : 40,
        "lvl"    : 50,
        "damage_type": "����"
]),
([      "action" : "$NȫȻ����$n����ʽ������$w����$n��ͷ����һ����",
        "force"  : 210,
        "dodge"  : -12,
        "parry"  : 30,
        "damage" : 50,
        "lvl"    : 80,
        "damage_type": "����"
]),
([      "action" : "$N��$w�߾ٹ��磬�����������׼$n��$l��������һ����",
        "force"  : 250,
        "dodge"  : -15,
        "parry"  : 35,
        "damage" : 60,
        "lvl"    : 100,
        "damage_type": "����"
]),
});

int valid_learn(object me)
{
    object ob;

    if( (int)me->query_skill("force", 1) < 30)
        return notify_fail("����ڹ���򻹲�����\n");

    if( (int)me->query_skill("hammer", 1) < 50)
        return notify_fail("��Ļ�������ˮƽ̫�͡�\n");

    if( (int)me->query("max_neili") < 250 )
        return notify_fail("��������������������Ͻ𴸷���\n");

    if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("zijin-chuifa", 1))
        return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������Ͻ𴸷���\n");

    if (!objectp(ob = me->query_temp("weapon"))
        || (string)ob->query("skill_type") != "hammer")
            return notify_fail("��ʹ�õ��������ԣ��޷���ϰ�Ͻ𴸷���\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="hammer" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int)me->query_skill("zijin-chuifa", 1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object ob;

    if ((int)me->query("qi") < 50)
        return notify_fail("�������̫�ͣ�û�а취��ϰ�Ͻ𴸷���\n");

    if ((int)me->query("neili") < 50)
        return notify_fail("�������������û�а취��ϰ�Ͻ𴸷���\n");

    if (!objectp(ob = me->query_temp("weapon"))
        || (string)ob->query("skill_type") != "hammer")
            return notify_fail("��ʹ�õ��������ԣ��޷���ϰ�Ͻ𴸷���\n");

    me->receive_damage("qi", 45);
    me->add("neili", -41);
    return 1;
}

