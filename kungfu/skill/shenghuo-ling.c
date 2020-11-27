#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N̤��һ���������ڵ���һ�����ѱ�ס��$nС�ȡ�ʮָ����$nС���ϵ��ж���"
                  "\n������Ѩ",
        "force" : 280,
        "attack": 100,
        "dodge" : 80,
        "damage": 120,
        "parry" : 70,
        "lvl"   : 0,
        "damage_type": "����"
]),
([      "action": "ͻȻ֮�䣬$N���λζ���ͬʱ�۽�������$w��$n���ϻ�ȥ�����²�֪����ƶ���"
                  "\n����ȴ����䡣����ͬʱץ��$n�ĺ���",
        "force" : 300,
        "attack": 120,
        "dodge" : 90,
        "parry" : 80,
        "damage": 130,
        "lvl"   : 40,
        "damage_type": "����"
]),
([      "action": "$N����ֱ�������ֳ�$w��$n����������䡣������һ˲֮�䣬$n����������"
                  "\nȻһȭ����$n�Ȳ���$nһ�����ģ�$N���$w����$n����",
        "force" : 340,
        "attack": 140,
        "dodge" : 100,
        "parry" : 90,
        "damage": 140,
        "lvl"   : 80,
        "damage_type": "����"
]),
([      "action": "$N���ط��֣������Ǳ�$wβ�����ϵ���ֱ��$n����",
        "force" : 360,
        "attack": 150,
        "dodge" : 110,
        "parry" : 100,
        "damage": 160,
        "lvl"   : 120,
        "damage_type": "����"
]),
([      "action": "$N��Ȼ��ͷ��һ��ͷ����$nײ����$n������ɫ����������һ�ã�ͻ���ؿ�һ��"
                  "\n���磬ֻ��$N����Ϯ��",
        "force" : 380,
        "attack": 160,
        "dodge" : 120,
        "parry" : 110,
        "damage": 170,
        "lvl"   : 160,
        "damage_type": "����"
]),
([      "action": "$N��Ȼ��ͷ��һ��ͷ����$nײ����$n������ɫ����������һ�ã�ͻ���ؿ�һ�飬"
                  "\n$N����$w���Ӻ�ɨ��ͻȻ�����������Ľ��$w�ѵ�$n�Ҽ�",
        "force" : 400,
        "attack": 170,
        "dodge" : 120,
        "parry" : 120,
        "damage": 180,
        "lvl"   : 180,
        "damage_type": "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query("int") < 32)
                return notify_fail("���������Բ��㣬�޷����ʥ�����\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("����ڹ���򲻵����޷�ѧϰʥ�����\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("��Ļ���������򲻵����޷�ѧϰʥ�����\n");

        if (me->query("int") < 32)
                return notify_fail("���������Բ��㣬�޷����ʥ�����\n");

        if (me->query("max_neili") < 2400)
                return notify_fail("����ڹ���Ϊ���㣬�޷�ѧϰʥ�����\n");

        if (me->query_str() < 35)
                return notify_fail("����������̫��޷�ѧϰʥ�����\n");

        if (me->query_int() < 40)
                return notify_fail("�������޷�����ʥ�����Ҫ�衣\n");

        if (me->query_dex() < 35)
                return notify_fail("��������̫��޷�ѧϰʥ�����\n");

        if (me->query_skill("force", 1) < me->query_skill("shenghuo-ling", 1))
                return notify_fail("����ڹ���Ϊ���㣬�޷����������ʥ�����\n");

        if (me->query_skill("shenghuo-ling", 1) > 200)
        {
             if ((me->query_skill("shenghuo-ling", 1))>(me->query_skill("shenghuo-shengong", 1)))
                            return notify_fail("���ʥ����ˮƽ���ޣ��޷����������ʥ�����\n");
        }
//                              return notify_fail("���ʥ����������޷���ϰ�������ʥ�����\n");

        if (me->query_skill("sword", 1) < me->query_skill("shenghuo-ling", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ʥ�����\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("shenghuo-ling", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) || 
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("shenghuo-ling", 1) < 180)
                return notify_fail("�㻹û������ʥ��������еİ���޷�"
                                   "ͨ���������������\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("�������������ʥ�����\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("�������������ʥ�����\n");

        me->receive_damage("qi", 50);
        me->add("neili", -70);

        return 1;
}

// ��Ӧperform canxue���ֶ���Ĺ���ЧӦ��
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (me->query_temp("shenghuo-ling/max_hit"))
        {
                victim->receive_wound("qi", damage_bonus);
                return HIR "ֻ�������͡�һ����һ����Ѫ��$n" HIR "��ǰ�����"
                       "\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-ling/" + action;
}

