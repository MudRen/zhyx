// qiluo-finger.c
// �������car���Դ��书���������
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "car";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "�������",
        "action":  "$N��������վ����˫�����ʮָ���裬ʹ��������������Ϯ��$n$l",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "����"
]),
([      "skill_name":    "�׺�����",
        "action":  "$Nɲ�Ǽ���շ��𣬽��ƿ���̤��������ӽ���һʽ���׺���������ָ������������$nȫ��",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "һ�����",
        "action":  "$N��������˲Ϣ��ӿ��һʽ��һ���������������ָ��չ���������磬ֱ����$n��$l",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "�������",
        "action":  "$Nʮָ�������ڿ��л�����ǧ���䣬һʽ��������ࡹ��Ʈ��$n",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "��ˮ����",
        "action":  "$N���ֳ���������$n������һָ������Ϣ�ĵ����һʽ����ˮ���꡹,Ϯ��$n$l",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "ɲ�Ƿ���",
        "action":  "$Nʮָ��������Ʈ�ɣ�����һ����̾���������������һʽ��ɲ�Ƿ���������$n$l",
        "dodge" : 115,
        "damage": 260,
        "force" : 410,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "������˭",
        "action":  "$N����ȫ������һʽ��������˭����ʮָ�����趯��ָ���ݺᣬ����$n$l",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("�������������û�а취�����������\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("�����ѧ����������û�а취�����������\n");

    if( (ob = me->query_temp("weapon")) || 
        (ob = me->query_temp("handing")) )
        return notify_fail("��ֻ�п���˫�ֲ�������ָ����\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="finger" || usage=="parry";
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("qiluo-finger",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("���������������ϰ���������\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("�������������û�а취��ϰ���������\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qiluo-finger/" + action;
}
