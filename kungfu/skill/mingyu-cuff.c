// mingyu-cuff.c
// �������blacksir���Դ��书������ȭ
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "blacksir";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "������",
        "action":  "ֻ��$N����һ�����������һ���������ڡ���׼$n�ı��Ӻ��������˹�ȥ",
        "dodge" : 80,
        "damage": 190,
        "force" : 340,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "skill_name":    "�β�Ѱ��",
        "action":  "$N����һ�֣���ȭ������һ�С��β�Ѱ�ߡ�����$n��$l�к���ȥ",
        "dodge" : 80,
        "damage": 190,
        "force" : 340,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "skill_name":    "Ҷ��͵��",
        "action":  "$N��ȭ��$n����һ�Σ�����ʹ�˸���Ҷ��͵�ҡ���$n��$l����һץ",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "����"
]),
([      "skill_name":    "�ڻ�����",
        "action":  "$N����һ������ȭ��������ȭ���磬һ�С��ڻ����ġ��Ʋ��ɵ��ػ���$n$l",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "˫����",
        "action":  "ֻ��$N������ʽ��һ�С�˫������ʹ�û����з硣����ȴ����һ������$n$l",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "�����ཻ",
        "action":  "$N������𣬴��һ�����������С������ཻ����\n������$n���һ������ȭ����$n�������˹�ȥ",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "����Ʊ�",
        "action":  "$N�����󹭲���˫��ʹ�˸�������Ʊա���$n��$lһ��",
        "dodge" : 110,
        "damage": 230,
        "force" : 380,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "����"
]),
([      "skill_name":    "��������",
        "action":  "ֻ��$N����������һ����ȭ����$n$l������һȭ�߹�һȭ��\n��һ�е����ֻ��൱���ţ�����������������",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "�����̸�",
        "action":  "$N����һ�ݣ�����ʹ�˸��������̸���������ɨ��$n��$l",
        "dodge" : 115,
        "damage": 260,
        "force" : 410,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "������ɽ",
        "action":  "$Nһ��ת�����ƻ��أ����Ʒ���ʹ�˸���������ɽ����$n��ͷһ��",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "����",
        "action":  "$N����Ծ�𣬰����һ������$n���ţ�ȴ�Ǹ����С�\n˵ʱ����ʱ�죬ֻ��$Nһ��������˫���ѵ���$n��$l",
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
        return notify_fail("�������������û�а취������ȭ��\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("�����ѧ����������û�а취������ȭ��\n");

    if( (ob = me->query_temp("weapon")) || 
        (ob = me->query_temp("handing")) )
        return notify_fail("��ֻ�п���˫�ֲ��������Ʒ���\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="cuff" || usage=="parry";
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
    level   = (int) me->query_skill("mingyu-cuff",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("���������������ϰ����ȭ��\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("�������������û�а취��ϰ����ȭ��\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"mingyu-cuff/" + action;
}
