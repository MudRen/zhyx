// nine-finger.c
// �������mfox���Դ��书������������ӡ
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "mfox";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "��������ӡ",
        "action":  "ֻ��$N���ָ߾ٹ�ͷ������������������ָб�����ǡ���������ӡ����\n"
                   "����������ɽ����ȫ��Ϊ$n����",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "����"
]),
([      "skill_name":    "������ӡ",
        "action":  "ֻ��$N˫�ֺ�ʲ���������֣�ʹ����������ӡ����ɭɭȭ���޼᲻�ݰ�ػ���$n",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "��ʨ��ӡ",
        "action":  "ֻ��$N���ֱ�ȭ�������ⷴ�����ǡ���ʨ��ӡ����\n"
                   "˫ȭ��ס�仯����$n��ǰ����������ӡ����$nһʱ��֪����",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "��ʨ��ӡ",
        "action":  "ֻ��$N����ֱ����ǰ���������գ����ǡ���ʨ��ӡ����\n"
                   "��һ�����벻���ĽǶ�ͻȻһȭ����$n��$l",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "�⸿ӡ",
        "action":  "ֻ��$N��������ӡ�ᣬ�仯�޷������ǡ��⸿ӡ������ȫ��$n������˫��֮��",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "����뺣��",
        "action":  "ֻ��$N����������ǰ�����ְ���ӡ�������Ƴ������ǡ��ڸ�ӡ����\n"
                   "��$n��$l���˹�ȥ����$n�޴Ӷ���",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "��ȭӡ",
        "action":  "ֻ��$N˫����ҡ������Ȱ�����$n��ǰ��˫ȭ�������ϻ���$n��$l��\n"
                   "˲��仯���ٶ���ӡ�䣬���ǡ���ȭӡ��",
        "dodge" : 115,
        "damage": 260,
        "force" : 410,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "����ӡ",
        "action":  "ֻ��$N��ǰ��������˷��ˣ�����������һ�С�����ӡ����\n"
                   "���������������ճ��������಻����$n����ӿȥ�����˶����˱�֮�⡣",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
([      "skill_name":    "��ƿӡ",
        "action":  "ֻ��$N������շ���˫�ְ��󡺱�ƿӡ����\n"
                   "ȭ�簵��������������������֮�����ӿ��е�ͷ��$n����������",
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
        return notify_fail("�������������û�а취������������ӡ��\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("�����ѧ����������û�а취������������ӡ��\n");

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
    level   = (int) me->query_skill("nine-finger",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("���������������ϰ����������ӡ��\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("�������������û�а취��ϰ����������ӡ��\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"nine-finger/" + action;
}