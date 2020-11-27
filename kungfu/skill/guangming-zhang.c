// guangming-zhang.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N˫��һ��һ�С�ħ����١��ó�������Ӱ£��$n��$l",
	"force" : 100,
	"dodge" : 5,
	"parry" : 1,
	"lvl" : 0,
	"damage" : 20,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ��һ�С�ʥ��С����ʽ�������ƴ�������$n��$l",
	"force" : 120,
	"dodge" : -2,
	"parry" : 2,
	"lvl" : 10,
	"damage" : 30,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ��һ�С�ʥ�������ʽ�������ƻ���Ϊʵ����$n��$l",
	"force" : 140,
	"dodge" : 3,
	"parry" : -2,
	"lvl" : 20,
	"damage" : 40,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ���������ơ�ʥ���תʽ��������Ȱ�����$n��ǰ��һ������$n��$l",
	"force" : 160,
	"dodge" : -5,
	"parry" : -1,
	"lvl" : 30,
	"damage" : 40,
	"damage_type" : "����"
]),
([      "action" : "$N˫��һ��ʹ����ʥ�������ɡ�����׼$n��$l�����ĳ�����",
	"force" : 180,
	"dodge" : -3,
	"parry" : 2,
	"lvl" : 40,
	"damage" : 50,
	"damage_type" : "����"
]),
([      "action" : "$N���ƻ��˸�ȦȦ�������Ƴ���һ�С�����巽�ġ�����$n$l",
	"force" : 200,
	"dodge" : 5,
	"parry" : -3,
	"lvl" : 50,
	"damage" : 50,
	"damage_type" : "����"
]),
([      "action" :"$Nʹ�����������Ƕϡ�������ɢ���ߴ�ͬʱ��$n��$l���ƹ���",
	"force" : 220,
	"dodge" : 1,
	"parry" : 1,
	"lvl" : 60,
	"damage" : 60,
	"damage_type" : "����"
]),
([      "action" : "$N����������һ�С����������졹˫�Ʋ����Ƴ�",
	"force" : 250,
	"dodge" : 4,
	"parry" : -1,
	"lvl" : 70,
	"damage" : 60,
	"damage_type" : "����"
]),
([      "action" : "$N���ƻ��˸�ȦȦ�������Ƴ���һ�С��������ķ�������$n$l",
	"force" : 280,
	"dodge" : 3,
	"parry" : 2,
	"lvl" : 80,
	"damage" : 70,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="shenghuo-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("strike", 1) < 10)
                return notify_fail("��Ļ����Ʒ���򲻹����޷����������ơ�\n");


        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guangming-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ĺ������ơ�\n");

	return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("guangming-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
                return notify_fail("������������ˡ�\n");

	me->receive_damage("qi", 20);
	me->add("neili", -30);
	return 1;
}

string perform_action_file(string action)
{
      return __DIR__"guangming-zhang/" + action;
}
