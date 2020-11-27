// shenghuo-quan.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N��ȭ��Σ���ȭ����������Ȼ�ɳ���������ͬ΢�紵���µĻ��棬��ֱϮ��$n",
	"force" : 100,
	"dodge" : 5,
	"parry" : 1,
	"lvl" : 0,
	"damage" : 20,
	"damage_type" : "����"
]),
([      "action" : "$N˫ȭ�����ȭ���Х����������ȭ��ֱָ$n��$l",
	"force" : 120,
	"dodge" : -2,
	"parry" : 2,
	"lvl" : 10,
	"damage" : 30,
	"damage_type" : "����"
]),
([      "action" : "$N������ȣ�����ȴ΢����ǰ����ȭƮ��������˸�Ļ�������²���������Ļ���$n",
	"force" : 140,
	"dodge" : 3,
	"parry" : -2,
	"lvl" : 20,
	"damage" : 40,
	"damage_type" : "����"
]),
([      "action" : "$N�������ˣ�����һȭ��������Ȼ�������������ȵľ�������$n��$l",
	"force" : 160,
	"dodge" : -5,
	"parry" : -1,
	"lvl" : 30,
	"damage" : 40,
	"damage_type" : "����"
]),
([      "action" : "$Nȭ�ƴ�ʢ����ͬ���е�������������Ʈ����$nֻ�о��������棬ȭ�д�����˷�Ϯ��",
	"force" : 180,
	"dodge" : -3,
	"parry" : 2,
	"lvl" : 40,
	"damage" : 50,
	"damage_type" : "����"
]),
([      "action" : "$N��ɫ���أ�һȭ��һȭͻȻ�����ޱȣ��������ն�����ȭ��ȴ��ͬ����ֱ��$n��$l",
	"force" : 200,
	"dodge" : 5,
	"parry" : -3,
	"lvl" : 50,
	"damage" : 50,
	"damage_type" : "����"
]),
([      "action" : "$N���μ�ת��������ң���ǰ����ȭ����ͬ���ڵĻ���ֱ��$n�к���ȥ",
	"force" : 220,
	"dodge" : 1,
	"parry" : 1,
	"lvl" : 60,
	"damage" : 60,
	"damage_type" : "����"
]),
([      "action" : "$N�ؿڿ��Ŵ󿪣�״��������˫ȭȴ����Χ�ϣ��д��Ź�������ֱ��$n",
	"force" : 250,
	"dodge" : 4,
	"parry" : -1,
	"lvl" : 70,
	"damage" : 60,
	"damage_type" : "����"
]),
([      "action" : "$N��¶����΢Ц���������ʢ����ȭ������ȭ��������������������ֱ��$n��$l��ȥ",
	"force" : 280,
	"dodge" : 3,
	"parry" : 2,
	"lvl" : 80,
	"damage" : 70,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "cuff" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="guangming-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��ʥ��ȭ������֡�\n");

        if ((int)me->query_skill("cuff", 1) < 10)
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷���ʥ��ȭ��\n");


        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("shenghuo-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷����������ʥ��ȭ��\n");

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
        level = (int)me->query_skill("shenghuo-quan", 1);
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
      return __DIR__"shenghuo-quan/" + action;
}
