#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N�������أ����е�$w����ǰ�ƶ���ͻȻһ�С�����ը�ա���$n��ȥ",
        "skill_name" : "����ը��",
        "force" : 320,
        "attack": 127,
        "dodge" : -30,
        "parry" : -34,
        "lvl"   : 0,
        "damage": 150,
        "damage_type" : "����",
]),
([      "action" : "$NԨͣ���ţ������͵��������ɣ�һ�С��ɾ���硹����է�ְ���$n��ȥ",
        "skill_name" : "�ɾ����",
        "force" : 460,
        "attack": 138,
        "dodge" : -27,
        "parry" : -45,
        "lvl"   : 40,
        "damage": 180,
        "damage_type" : "����",
]),
([      "action" : "$NͻȻ����һ���������$wһ�죬һ�С���񷿪�ơ��͵�����$n��ȥ",
        "skill_name" : "��񷿪��",
        "force" : 500,
        "attack": 143,
        "dodge" : -25,
        "parry" : -47,
        "lvl"   : 80,
        "damage": 200,
        "damage_type" : "����",
]),
([      "action" : "$Nб������������$w�������󺮹⣬��Ȼ��һ�С�������ա�����$n",
        "skill_name" : "�������",
        "force" : 520,
        "attack": 151,
        "dodge" : -45,
        "parry" : -50,
        "lvl"   : 120,
        "damage": 220,
        "damage_type" : "����",
]),
([      "action" : "$N˫��һ�٣�һ�С��������ǡ������е�$w�Լ�����ٶ���$n��������",
        "skill_name" : "��������",
        "force" : 530,
        "attack": 155,
        "dodge" : -20,
        "parry" : -25,
        "lvl"   : 160,
        "damage": 240,
        "damage_type" : "����",
]),
([      "action" : "$N��$w�����������������ʹ�˲��ҿ������͵�һ�С���ڤǧ������$n��ȥ",
        "skill_name" : "��ڤǧ��",
        "force" : 550,
        "attack": 165,
        "dodge" : -40,
        "parry" : -35,
        "lvl"   : 180,
        "damage": 260,
        "damage_type" : "����",
]),
([      "action" : "$N���е�$w��������һ��������෭������������һ�С���徵���������$n",
        "skill_name" : "��徵���",
        "force" : 570,
        "attack": 184,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 220,
        "damage": 280,
        "damage_type" : "����",
]),
([      "action" : "$N����ָ�죬�����������Ȼʩ��һ�С���Ѫ���졹����ʮ���������$n",
        "skill_name" : "��Ѫ����",
        "force" : 580,
        "attack": 197,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 260,
        "damage": 300,
        "damage_type" : "����",
]),
([      "action" : "$NͻȻһ�С������޻��������е�$w�������е�һ�����������$n",
        "skill_name" : "�����޻�",
        "force" : 610,
        "attack": 209,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 280,
        "damage": 320,
        "damage_type" : "����",
]),
([      "action" : "$NһԽ�οգ���Х����������ʩһ�С�������ǡ���$w����һ����������$n",
        "skill_name" : "�������",
        "force" : 640,
        "attack": 230,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 300,
        "damage": 340,
        "damage_type" : "����",
]),
});


int valid_enable(string usage)
{
	return usage == "hammer" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query("str") < 35)
                return notify_fail("������������������޷���������������\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("���������Ϊ̫ǳ���޷���������������\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ����̫ǳ���޷���������������\n");

        if ((int)me->query_skill("hammer", 1) < 180)
                return notify_fail("��Ļ����������̫ǳ���޷���������������\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("leiting-fu", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("leiting-fu",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        weapon = me->query_temp("weapon");      

        if ((damage_bonus / 4 > victim->query_str()) )
        {
                victim->receive_wound("qi", (damage_bonus - 110) / 2, me);
                return RED "ֻ��" +weapon->name()+ RED"��һ�����籼��"+ victim->name() + RED "��˲�佦��һ��Ѫ�꣡\n" NOR;
        }

        return 1;                         
}



int practice_skill(object me)
{
        object weapon;

        if (me->query_skill("leiting-fu", 1) < 260)
                return notify_fail("������������˽ⲻ���������������ж�����\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "hammer")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 130)
                return notify_fail("�����������������������������\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�����������������������������\n");

        me->receive_damage("qi", 100);
        me->add("neili", -150);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"leiting-fu/" + action;
}
