#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N˫��һ�������ƴ��ŵ��������⣬ֱ��$n��ȥ",
        "$N������Σ�����ֱ�������綾��һ��ֱ��$n����ǰ",
        "$N˫�Ʒ��ɣ�������ã��һ�ɰ���������������$n��ȫ��",
        "$N����һ�֣�������Ы���������ߣ�ͬʱ��$n����ȥ",
        "$NĬ��������˫�ƺ�Ȼ��ڣ�����һ������ֻ��$n��ȫ��",
});

int valid_enable(string usage)
{
        return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("��Ļ����Ʒ���򲻹����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chilian-shenzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĳ������ơ�\n");

        return 1;
}

mapping query_action(object me)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(60), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : random(2) ? "����" : "����", 
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 60)
                return notify_fail("��������������������ơ�\n");

        me->receive_damage("qi", 61);
        me->add("neili", -53);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chilian-shenzhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chilian-shenzhang", 1);
        flvl = me->query("jiali");
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "name"  : "�������ƶ�",
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "��Ȼ����һ����Ϯ��������һ�Σ�ͷ��΢΢��Щ���衣\n" NOR;
        }
}
