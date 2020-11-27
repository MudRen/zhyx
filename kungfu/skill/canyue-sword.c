// canyue-sword.c

#include <ansi.h>

inherit SKILL;


mapping *action = ({
([      "skill_name":    "׷�����",
        "action":  "$N�߾�����$w,ʹ��һ�С�׷����硹��һ��б��$n��$l",
        "dodge" : 80,
        "damage": 120,
        "force" : 330,
        "attack": 120,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "skill_name":    "ն��ɱ��",
        "action":  "$N�͵�һ����ʹһ�С�ն��ɱ����������$w��һ���޷�˼��ĽǶȻ���$n��$l",
        "dodge" : 90,
        "damage": 130,
        "force" : 360,
        "attack": 130,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "����"
]),
([      "skill_name":    "˭��Ӣ��",
        "action":  "$N���е�$w��â������ʹ����˭��Ӣ�ۡ����������������$n��$l",
        "dodge" : 95,
        "damage": 140,
        "force" : 390,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "����"
]),
([      "skill_name":    "��ɽ����",
        "action":  "$Nһ�п���ƽ������ġ���ɽ���꡹��$w�����һ����˿��$n��ȥ",
        "dodge" : 105,
        "damage": 150,
        "force" : 420,
        "attack": 150,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "����"
]),
([      "skill_name":    "�߲�ʤ��",
        "action":  "$N���˺�һ�����⽻�ڣ�����$w����������$n��$l",
        "dodge" : 110,
        "damage": 160,
        "force" : 440,
        "attack": 160,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "����"
]),
([      "skill_name":    "�ػ��˼�",
        "action":  "$N����������е�$w�ó�һƬ���⣬��Ȼ����һ����ն$n��$l",
        "dodge" : 115,
        "damage": 170,
        "force" : 460,
        "attack": 170,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "����"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 3000 )
        return notify_fail("�������������û�а취�����½�����\n");
    
    if (me->query("int") < 30)
                return notify_fail("���������Բ��㣬������ϰ���½�����\n");   

    if( (int)me->query_skill("martial-cognize",1) < 250 )
        return notify_fail("�����ѧ����������û�а취�����½�����\n");

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
    level   = (int) me->query_skill("canyue-sword",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 80)
        return notify_fail("���������������ϰ���½�����\n");

    if ((int)me->query("neili") < 80 )
        return notify_fail("�������������û�а취��ϰ���½�����\n");

    me->receive_damage("qi", 140);
    me->add("neili", -120);

    return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (me->query_temp("canyue-sword/max_pfm") && random(5)>2)
        {
                victim->receive_wound("qi", (damage_bonus - 120) / 4, me);
                return HIB "�ǹ���ǧ�����¶��𣡣�\n" NOR;                                   
        }
}


string perform_action_file(string action)
{
        return __DIR__"canyue-sword/" + action;
}
