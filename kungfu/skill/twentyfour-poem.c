// twentyfour-poem.c
// �������yxer���Դ��书��ʫ����ʮ��Ʒ
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "yxer";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "Ʈ��",
        "action":  "$Nӭ���ҡֱ�ϣ�ȭ�硸Ʈ�ݡ�����Ѱ������϶����Ȼ����$n",
        "dodge" : 80,
        "damage": 190,
        "force" : 340,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "skill_name":    "�嵭",
        "action":  "$N��ȻһЦ��˫��������չ����������������ȴ��$n�޴ӳ��֡�����$n���ͣ����г��У�һ�С��嵭���Ѻ�����",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "����"
]),
([      "skill_name":    "�˷v",
        "action":  "$N�������ԣ�һʽ���˷v����˫��һ��������ӭ�磬����΢�ų�ָ���ˣ����ֽ��ճ�ȭ���v�������������������ֱ��$n������ȥ",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "����",
        "action":  "$N���Ʋ��ɲ�����ɽ����������ΡȻ�����ǲ��ܲ�ӭ��˫ȭֱ��������һ���������$n�յ���",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "���",
        "action":  "$N˫�����������²�ͣ���������裬������ȫ���������ţ�˫ȭ����մ�һ��һ���������ഥ������$nֻ�����컨���������������������������������",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "����",
        "action":  "$N������ָ΢�������黨״������������һĨһ����$n����Ȼ�䣬һʽȭ����������Ϣӭ��",
        "dodge" : 110,
        "damage": 230,
        "force" : 380,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "����"
]),
([      "skill_name":    "ί��",
        "action":  "$N���κ�����ֱ��������������ң�������ˮ����������ƫ������������$n���޴����У����Ǽ�����Լ֮����ί����",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "����",
        "action":  "$Nһ�������š�����Ȼ�ְ���ȭ��ʢʢ����������ˮ����ľΪ�ݣ������������࿹",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "����",
        "action":  "$N��Ĭ���������תȫ������ֱ����й������֮�ڣ�����һ˿�ճ�פ�㣬����Ц�У�ٲȻ��������֮Բ�룬�ַ��Ǵ�Į���̣�ȭ��ֱ��ֱȥ�����������",
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
        return notify_fail("�������������û�а취��ʫ����ʮ��Ʒ��\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("�����ѧ����������û�а취��ʫ����ʮ��Ʒ��\n");

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
    level   = (int) me->query_skill("twentyfour-poem",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("���������������ϰʫ����ʮ��Ʒ��\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("�������������û�а취��ϰʫ����ʮ��Ʒ��\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"twentyfour-poem/" + action;
}
