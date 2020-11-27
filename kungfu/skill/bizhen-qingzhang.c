#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N���μ��Σ�һԾ����$n��ǰ�����ƴ����й�֮������$n��$l",
        "force" : 300,
        "attack": 100,
        "dodge" : 80,
        "parry" : 80,
        "damage": 140,
        "lvl"   : 0,
        "damage_type" : "����"
]),
([      "action" : "$N����Ծ��˫�����϶���б����������ʱ��ǧ���ƺ���������˷�ϯ��$n",
        "force" : 350,
        "attack": 150,
        "dodge" : 100,
        "parry" : 100,
        "damage": 150,
        "lvl"   : 50,
        "damage_type" : "����"
]),
([      "action" : "$Nƽ��Ϊ����бб�������ó�һ�������͵��ƾ���쫷�����$n��ȫ��",
        "force" : 400,
        "attack": 180,
        "dodge" : 120,
        "parry" : 120,
        "damage": 160,
        "lvl"   : 100,
        "damage_type" : "����"
]),
([      "action" : "$N��ת���ƻ�סȫ��������Ծ��$n��ǰ����ע���ƣ�����$n������ȥ",
        "force" : 450,
        "attack": 190,
        "dodge" : 130,
        "parry" : 130,
        "damage": 170,
        "lvl"   : 150,
        "damage_type" : "����"
]),
([      "action" : "$N���ƺ󳷣�����һ�����͵ػ��ƿ������ó�һ���ޱ��������ƾ�ֱն��$n��$l",
        "force" : 500,
        "attack": 200,
        "dodge" : 140,
        "parry" : 140,
        "damage": 180,
        "lvl"   : 200,
        "damage_type" : "����"
]),
([      "action" : "$N˫�ֻ�������γ�һ����Ȧ��һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
        "force" : 550,
        "attack": 220,
        "dodge" : 150,
        "parry" : 150,
        "damage": 200,
        "lvl"   : 250,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
//        if (me->query("character") == "���ռ�թ")
//                return notify_fail("�����а��룺���书�����ý���ѧ��������\n");

        if ((int)me->query("str") < 38)
                return notify_fail("��������������������������������ơ�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���򲻹����޷���ϰ�������ơ�\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("�������̫�����޷���ϰ�������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("��Ļ����Ʒ���򲻹����޷���ϰ�������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bizhen-qingzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ı������ơ�\n");

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
        level = (int) me->query_skill("bizhen-qingzhang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        int cost;

        if ((int)me->query("str") < 38)
                return notify_fail("��������������������������������ơ�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query("qi") < 200)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("��������������������ơ�\n");

        cost = me->query_skill("bizhen-qingzhang", 1) / 2 + 100;

        me->receive_damage("qi", 100);
        me->add("neili", -cost);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("bizhen-qingzhang", 1);

        if (damage_bonus < 100 || lvl < 150 ) return 0;

        if (random(me->query_skill("force")) > victim->query_skill("force") / 3)
        {
                victim->receive_wound("qi", (damage_bonus - 50) / 2);
                return HIR "ֻ��" + victim->name() +
                       HIR "ǰ�ء����ꡱһ�����������߹���ϵ�������\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bizhen-qingzhang/" + action;
}
