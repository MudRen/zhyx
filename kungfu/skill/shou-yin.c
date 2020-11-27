// shou-yin.c ��ӡ(������)

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹ��һ�С���������ӡ����˫����׶��ֱֱ����$n��ǰ��",
        "force"    : 400,
        "attack"   : 220,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 200,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ƹ���ӡ��������Ծ��˫���繴��ץ��$n��$l",
        "force"    : 440,
        "attack"   : 240,
        "dodge"    : 140,
        "parry"    : 140,
        "damage"   : 250,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�׼���ĸӡ����������ָ��ֱȡ$n��$l",
        "force"    : 480,
        "attack"   : 240,
        "dodge"    : 150,
        "parry"    : 150,
        "damage"   : 280,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С���������ӡ����ŭ��һ����һ�Ƶ�ͷ����$n��$l",
        "force"    : 520,
        "attack"   : 260,
        "dodge"    : 160,
        "parry"    : 160,
        "damage"   : 300,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�ҩʦ�����ӡ�����ͳ���ǰ���Ƶ��������㿳��$n",
        "force"    : 540,
        "attack"   : 260,
        "dodge"    : 180,
        "parry"    : 180,
        "damage"   : 320,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����½��ӡ������������˫������ɨ��$n��$l",
        "force"    : 560,
        "attack"   : 280,
        "dodge"    : 200,
        "parry"    : 200,
        "damage"   : 340,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ֽ��ӡ���������Ծ��˫��ǰ�������ץ��$n����"
                   "��",
        "force"    : 580,
        "attack"   : 290,
        "dodge"    : 210,
        "parry"    : 210,
        "damage"   : 350,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С������ǻ�ӡ������ʱ��������������г���������Ӱ��"
                   "��$n",
        "force"    : 600,
        "attack"   : 300,
        "dodge"    : 220,
        "parry"    : 220,
        "damage"   : 360,
        "weapon"   : HIW "��ӡ" NOR,
        "damage_type" : "����",
]),
});

int double_attack() { return 1; }

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ӡ������֡�\n");

        if (me->query("str") < 34)
                return notify_fail("��ı����������޷���ϰ��ӡ��\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("�����ѧ����̫�ͣ��޷���ϰ��ӡ��\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("hand", 1) < 200)
                return notify_fail("��Ļ����ַ����̫ǳ��\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("shou-yin",1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷������������ӡ��\n");

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
                  level   = (int) me->query_skill("shou-yin",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������ӡ��������֡�\n");

        if ((int)me->query("qi") < 800)
                return notify_fail("���������������������ӡ��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("���������������������ӡ��\n");

        me->receive_damage("qi", 500 + random(200));
        me->add("neili", -500 - random(200));
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100) return 0;

        if (damage_bonus / 6 > victim->query_str())
        {
                victim->receive_wound("qi", (damage_bonus - 140) / 2);
                return HIR "ֻ��" + victim->name() +
                       HIR "һ���ƺߣ�һ˫" NOR + HIW "��ӡ"
                       NOR + HIR "���ص�ӡ����ǰ�����ۡ�"
                       "�������һ�����Ѫ��\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"shou-yin/" + action;
}

