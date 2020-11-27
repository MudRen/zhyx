#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N����$wһת������һ��������$n$l������һ�С��ؽ�ʽ��",
        "force"  : 120,
        "dodge"  : 80,
        "parry"  : 70,
        "attack" : 100,
        "damage" : 90,
	"lvl"    : 0,
        "damage_type" : "����",
        "skill_name"  : "�ؽ�ʽ",
]),
([      "action" :  "ֻ��$N����Ȼ�ӿ죬ʩչ��������ʽ�������絴����$w˲������$n$l",
        "force"  : 160,
        "dodge"  : 85,
        "parry"  : 75,
        "attack" : 110,
        "damage" : 100,
	"lvl"    : 25,
        "damage_type" : "����",
        "skill_name"  : "����ʽ",
]),
([      "action" : "$N����Ծ��ʹ��һ�С��佣ʽ��������$w�Ӱ��ֱָ$N$l",
        "force"  : 200,
        "dodge"  : 90,
        "parry"  : 80,
        "attack" : 120,
        "damage" : 110,
	"lvl"    : 50,
        "damage_type" : "����",
        "skill_name"  : "�佣ʽ",
]),
([      "action" : "$N�ڿն���һ�С�����ʽ��������׼�ֿ죬����$w�ѵ�$n$l",
        "force"  : 220, 
        "dodge"  : 95,
        "parry"  : 85,
        "attack" : 130,
        "damage" : 120,
	"lvl"    : 75,
        "damage_type" : "����",
        "skill_name"  : "����ʽ",
]),
([      "action" : "$N�����ת��һ����ֱ����$n$l�������ھ�ʮ�㣬����һ�С�ƽ��ʽ��",
        "force"  : 240,
        "dodge"  : 100,
        "parry"  : 90,
        "attack" : 140,
        "damage" : 130,
	"lvl"    : 100,
        "damage_type" : "����",
        "skill_name"  : "ƽ��ʽ",
]),
([      "action" : "$N����$w��Ȼ�س���������һ�������ư��磬�����ݺᣬ���ǡ�����ʽ��",
        "force"  : 260,
        "dodge"  : 105,
        "parry"  : 95,
        "attack" : 160,
        "damage" : 140,
	"lvl"    : 120,
        "damage_type" : "����",
        "skill_name"  : "����ʽ",
]),
});

int valid_learn(object me)
{
        object ob;

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
                return notify_fail("���������һ�ѽ�������������\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("���������Ϊ�������޷�ѧϰ�ط����㽣��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ���޷�ѧϰ�ط����㽣��\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ�ط����㽣��\n");

        if (me->query_skill("sword", 1) < me->query_skill("luoyan-jian", 1))
		return notify_fail("��Ļ�������������ޣ��޷���������Ļط����㽣��\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
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

        level = (int) me->query_skill("luoyan-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
       object weapon;

       if (! objectp(weapon = me->query_temp("weapon"))
          || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

       if((int)me->query("neili") < 30 )
        	   return notify_fail("����������㣬û�а취��ϰ�ط����㽣��\n");

       if ((int)me->query("qi") < 35)
        	   return notify_fail("��������������ط����㽣��\n");

       me->receive_damage("qi", 40);
       me->add("neili", -50);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoyan-jian/" + action;
}

