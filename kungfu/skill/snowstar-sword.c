// snowstar-sword.c
// �������fastidium���Դ��书��ѩӰ���ǽ���
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "fastidium";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "ǧ�����",
        "action":  "$NĬ��������һ����͸������ңָ$n��$n��ʱ���ĵ׷���һ�ɺ��⣬�·���������������֮��",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "skill_name":    "�����岼",
        "action":  "$Nһ������$w����㺮��ƮƮ��������$n",
        "dodge" : 90,
        "damage": 190,
        "force" : 340,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "����"
]),
([      "skill_name":    "�׷�ѩ��",
        "action":  "$N�趯����$w����ѩ���׷ɣ�����ˮ��к�أ���㽣������$n��$nֻ����ǰ������˸��һʱ��֪����м�",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "���ǵ���",
        "action":  "$NǱ������ ��˫�ֽ���$w���˽���һ����������$n��ȥ",
        "dodge" : 105,
        "damage": 210,
        "force" : 360,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "��ɽѩӰ",
        "action":  "$Nִ����������̨��������Χ����һ�㺮���������Ȼ����Ϊһ�壬���е�$w��������$n��$l",
        "dodge" : 110,
        "damage": 220,
        "force" : 370,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "����"
]),
([      "skill_name":    "��������",
        "action":  "$N˫Ŀ���գ�������մ�����������$n��ʱ������·����ǰһ����$w��ӭ�����",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
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
        return notify_fail("�������������û�а취��ѩӰ���ǽ�����\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("�����ѧ����������û�а취��ѩӰ���ǽ�����\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
        return notify_fail("���������һ�ѽ�������������\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
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
    level   = (int) me->query_skill("snowstar-sword",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("���������������ϰѩӰ���ǽ�����\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("�������������û�а취��ϰѩӰ���ǽ�����\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"snowstar-sword/" + action;
}
