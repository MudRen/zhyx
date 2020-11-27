// ���վ��� shenzhaojing.c
// Editd By Vin On 26/4/2001
// Modified By xiner 28/3/2009 ����Ϊת���߼�SK��������ר��

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenzhaojing", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

mapping *action = ({
([      "action" : "$NٿȻԾ��������һȭ����һȭ������Ӱ��ȥ�ƿ켫����$n���ؿڴ�ȥ",
        "dodge"  : 180,
        "force"  : 350,
        "attack" : 150,
        "parry"  : 100,
        "damage" : 150,
        "lvl"    : 0,
        "damage_type": "����" 
]), 
([      "action" : "$N˿��������ɫ������ƽ�죬�����������վ��񹦵ľ���������һ������$n",
        "dodge"  : 200,
        "force"  : 400,
        "attack" : 150,
        "parry"  : 150,
        "damage" : 180,
        "lvl"    : 200,
        "damage_type": "����"
]), 
([      "action" : "$N����΢΢һչ����Ȼ������$n��ǰ����Ȼ��˫����ʩ����$n���Ķ�ȥ",
        "dodge"  : 210,
        "force"  : 450,
        "attack" : 200,
        "parry"  : 200,
        "damage" : 200,
        "lvl"    : 220,
        "damage_type": "����"
]),
([      "action" : "$N�˺�һ����˫�ƻ��գ���ջ���һ��ԲȦ����ʱһ�����ȵ�����ֱӿ$n����",
        "dodge"  : 210,
        "force"  : 500,
        "attack" : 250,
        "parry"  : 250,
        "damage" : 300,
        "lvl"    : 250,
        "damage_type": "����"
]), 
});

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

int valid_enable(string usage)
{ 
        int lvl;
        lvl = (int)this_player()->query_skill("shenzhaojing", 1);

        if(lvl >= 180)    
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";
       
}

int valid_learn(object me)
{
        if ((int)me->query("str") < 48)
                return notify_fail("�����������������޷��������վ��񹦡�\n");

        if ((int)me->query("con") < 42)
                return notify_fail("����������������޷��������վ��񹦡�\n");

	if ((int)me->query("int") > 14 && (int)me->query_skill("shenzhaojing", 1) > 100)
                return notify_fail("����������̫�࣬����������������վ��񹦡�\n");

        if ( me->query("gender") == "����" && me->query("shenzhaojing", 1) > 29)
                return notify_fail("���޸����ԣ�������������������������վ��񹦡�\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ���վ��񹦡�\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("��Ļ���ȭ�Ż���㣬����ѧ���վ��񹦡�\n");

        if ((int)me->query("max_neili", 1) < 4000)
                return notify_fail("���������Ϊ���㣬����ѧ���վ��񹦡�\n");

        if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ������������վ��񹦡�\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���������Զ������������վ��񹦡�\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("shenzhaojing", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("shenzhaojing", 1);

        if (damage_bonus < 160
           || lvl < 180
           || me->query("neili") < 300
           || me->query_temp("weapon")
           || me->query_temp("secondary_weapon")
           || me->query_skill_mapped("force") != "shenzhaojing"
           || me->query_skill_mapped("unarmed") != "shenzhaojing"
           || me->query_skill_prepared("unarmed") != "shenzhaojing")
                return 0;

        // ���վ��������еļ���������˺���ʹ������
        // ����max_hit �������书���Ǿ��޽��еģ�����
        // �����ֵļ����Լ��˺�ֵ�ּ������˺��������
        // ���书��������
        if (damage_bonus / 5 > victim->query_con())
        {
		victim->receive_wound("qi", (damage_bonus - 50) / 3, me);
		victim->affect_by("shenzhao",
			([ "level" : me->query("jiali") + random(me->query("jiali")),
				"id"    : me->query("id"),
				"duration" : lvl / 100 + random(lvl / 10) ]));
		return HIR "$n" HIR "һ���Һ���ȫ��������������"
                       "�����߹ǡ��۹ǡ��ȹ�ͬʱ���ۡ�\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("���վ���ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level()
{
        return 700;
}

string perform_action_file(string action)
{
        return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"shenzhaojing/exert/" + action;
}
