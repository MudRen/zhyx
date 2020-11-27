// ��������
// Updated by Lonely

inherit SKILL;

mapping *action = ({
([      "action" : "$N˫��Ʈ������,ͻȻ�Ӳ�����˼��ĽǶȣ�����$n���ؿ�",  
        "dodge" : 50,
        "damage": 60,
        "lvl" : 10,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$N��Хһ����ƽ�ط������ɣ��Ӹ����½���ͷ�£�˫���ص���һ���˾�ѹ����֣�$n��ʧɫ",  
        "dodge" : 60,
        "damage": 100,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$n��ǰһ����ʧȥ$N����Ӱ��ֻ�����������һ���Ʒ磬ֻ��$N˫��ͬʱ����$n����Ҫ��",  
        "dodge" : 70,
        "damage": 80,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$N��ָ��������ò�ʩ������$n����·Ҫ��",  
        "dodge" : 90,
        "damage": 100,
        "lvl" : 10,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$N��������������˷�����������Ӱ��һ��ͻ���������������֮ʽ����$n",
        "dodge" : 120,
        "damage": 150,
        "lvl" : 80,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
});

string *parry_msg = ({
        "$Nһ�л���$n���ϣ�ȴ��$n������ȥ��\n",
        "$n����һ����$N�����Լ�����������ա�\n",
        "$n��ǣ������$N��������������ת�˺ü���Ȧ��\n",
        "$n����һת��$Nһ�л��ڵ��ϣ�ֻ��ó������\n",
});
int valid_enable(string usage) 
{ 
        return (usage == "hand") || (usage == "parry");
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������������֡�\n");
        if ((int)me->query_skill("biyun-xinfa", 1) < 10)
                return notify_fail("��ı����ķ���򲻹����޷�ѧ��������\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷�����������\n");
        return 1;
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
        level = (int) me->query_skill("boyun-suowu",1);
        for( i = sizeof(action); i > 0; i-- )
                if( level > action[i-1]["lvl"] )
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 100)
                return notify_fail("���������������������\n");
        me->receive_damage("qi", 25);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"boyun-suowu/" + action;
}

int query_effect_parry(object attacker, object me) 
{
        int lvl;

        lvl = me->query_skill("boyun-suowu", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

