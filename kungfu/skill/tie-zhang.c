#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N����һ������ʩ�����ƴ����¡��Բ����������򣬵�ʱ��$n������б",
        "force"  : 200,
        "attack" : 100,
        "dodge"  : 50,
        "parry"  : 50,
        "damage" : 70,
        "lvl"    : 0,
        "skill_name" : "�ƴ�����",
        "damage_type": "����"
]),
([      "action": "$Nʩ������ˮ�����������ƶ�Ȼ�����쳤���ұ�һ��������ն��$n��$l",
        "force"  : 230,
        "attack" : 110,
        "dodge"  : 60,
        "parry"  : 60,
        "damage" : 75,
        "lvl"    : 40,
        "skill_name" : "�ƴ�����",
        "damage_type": "����"
]),
([      "action": "$Nһ�С����ƻ��衹��˫��������һ��һ����裬����һ����ת������",
        "force"  : 260,
        "attack" : 120,
        "dodge"  : 70,
        "parry"  : 70,
        "damage" : 80,
        "lvl"    : 80,
        "skill_name" : "�ƴ�����",
        "damage_type": "����"
]),
([      "action": "$N��Ȼһ�С�����Ǭ����������������ұ��������·�����ֱ����$n��ȥ",
        "force"  : 290,
        "attack" : 130,
        "dodge"  : 80,
        "parry"  : 80,
        "damage" : 85,
        "lvl"    : 120,
        "skill_name" : "����Ǭ��",
        "damage_type": "����"
]),
([      "action": "$Nһ�С����ո��¡�������һ��һ�գ���ʱһ�������ޱȵ�������$n��ȥ",
        "force"  : 320,
        "attack" : 140,
        "dodge"  : 90,
        "parry"  : 90,
        "damage" : 90,
        "lvl"    : 160,
        "skill_name" : "���ո���",
        "damage_type": "����"
]),
([      "action": "$N���б���һʽ������Ϊ������˫�ƺ����$n�г������غ�Х֮������",
        "force"  : 350,
        "attack" : 150,
        "dodge"  : 67,
        "parry"  : 90,
        "damage" : 95,
        "lvl"    : 180,
        "skill_name" : "����Ϊ��",
        "damage_type": "����"
]),
([      "action": "$Nһ�С����޵����������ƴ�Ȧ����������СȦ��������������ͬʱ����$n",
        "force"  : 380,
        "attack" : 160,
        "dodge"  : 100,
        "parry"  : 100,
        "damage" : 100,
        "lvl"    : 200,
        "skill_name" : "���޵���",
        "damage_type": "����"
]),
([      "action": "$Nʩһ�С���ָ��ɽ���������������ţ���һ��ȴ��Ѹ���ޱȵ�һ�Ƽ���",
        "force"  : 410,
        "attack" : 170,
        "dodge"  : 110,
        "parry"  : 110,
        "damage" : 105,
        "lvl"    : 220,
        "skill_name" : "��ָ��ɽ",
        "damage_type": "����"
]),
([      "action": "$NͻȻ���һ����һ�С����������������м��ɶ���������$nֱ�˶���",
        "force"  : 440,
        "attack" : 180,
        "dodge"  : 110,
        "parry"  : 110,
        "damage" : 110,
        "lvl"    : 240,
        "skill_name" : "��������",
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʒ�������֡�\n");

        if (me->query("str") < 32)
                return notify_fail("�����������������������������Ʒ���\n");

        if (me->query("con") < 32)
                return notify_fail("�����������������������������Ʒ���\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("���������Ϊ̫�����������������Ʒ���\n");

        if ((int)me->query_skill("force") < 230)
                return notify_fail("����ڹ�����㣬�������������Ʒ���\n");

        if ((int)me->query_skill("strike", 1) < 150)
                return notify_fail("��Ļ����Ʒ���򲻹����������������Ʒ���\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tie-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������������Ʒ���\n");

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
        level = (int) me->query_skill("tie-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

int practice_skill(object me)
{
        int cost;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʒ�������֡�\n");

        if ((int)me->query("qi") < 150)
                return notify_fail("�������̫���ˡ�\n");

        cost = me->query_skill("tie-zhang", 1) / 5 + 80;

        if ((int)me->query("neili") < cost)
                return notify_fail("������������������Ʒ���\n");

        me->receive_damage("qi", 120);
        me->add("neili", -cost);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("tie-zhang", 1);

        if (damage_bonus < 120 || lvl < 150)
                return 0;

        if (damage_bonus / 5 > victim->query_con()
            && random(2) == 1)
        {
                victim->receive_wound("qi", (damage_bonus - 75) / 3, me);

                return random(2) ? HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������"
                                   "�߹Ƕ��۵�������\n" NOR:

                                   HIR "$n" HIR "һ���ҽУ���ǰ���������꡹������"
                                   "�죬������Ѫ���硣\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"tie-zhang/" + action;
}
