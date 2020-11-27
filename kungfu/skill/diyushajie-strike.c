// diyushajie-strike.c
// �������sker���Դ��书������ɱ���Ʒ�
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "sker";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "����ɱ",
        "action":  "$N��ǰб��һ����һ�С�����ɱ�������в���$n��$l",
        "dodge" : 80,
        "damage": 190,
        "force" : 340,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "skill_name":    "��ɲɱ",
        "action":  "$N˫��������צ��צצ����$n������ɲɱ������$n��$lץȥ",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "ץ��"
]),
([      "skill_name":    "����ɱ",
        "action":  "$N��ȭ��Σ���ָ������һ�С�����ɱ��ֱ����$n��$1",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "ڤ��ɱ",
        "action":  "$N���һ��������һ���죬˫�ۺ�Ȼ�������ߣ�һ�С�ڤ��ɱ��ֱֱ����$n��$l",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "����ɱ",
        "action":  "$N����һԾ����һ���ֽУ�һ�С�����ɱ����˫������ǵذ�����$n",
        "dodge" : 110,
        "damage": 230,
        "force" : 380,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "����"
]),
([      "skill_name":    "��ħɱ",
        "action":  "$Nʹ��һ�С���ħɱ����˫�Ƽ��������������������Ʒ�ֱ��$n��$l",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "��ڤɱ",
        "action":  "$N˫��Ѫ�죬һʽ����ڤɱ�����ó������Ӱ��������$n��ȥ",
        "dodge" : 115,
        "damage": 260,
        "force" : 410,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "����ɱ",
        "action":  "$N��Ȼһ����Х��һ�С�����ɱ����˫����Ȼ���£������׵�ֱ��$n��$l",
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
        return notify_fail("�������������û�а취������ɱ���Ʒ���\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("�����ѧ����������û�а취������ɱ���Ʒ���\n");

    if( (ob = me->query_temp("weapon")) || 
        (ob = me->query_temp("handing")) )
        return notify_fail("��ֻ�п���˫�ֲ��������Ʒ���\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="strike" || usage=="parry";
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
    level   = (int) me->query_skill("diyushajie-strike",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("���������������ϰ����ɱ���Ʒ���\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("�������������û�а취��ϰ����ɱ���Ʒ���\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"diyushajie-strike/" + action;
}
