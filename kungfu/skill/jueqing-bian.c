// jueqing-bian.c  ����޷�

#include <ansi.h>

inherit SKILL;
#include <ansi.h>
#include <combat.h>
int sanwu
(object me, object victim, object weapon, int damage);

mapping *action = ({
([	"action":		"$N�ᶶ����һ�С�������о��������$w���ñ�ֱ��ֱ��$n��ȥ",
	"force":		60,
	"dodge":		-30,
	"damage":		30,
	"lvl" : 0,
	"skill_name" : "������о",
	"damage_type":	"����"
]),
([	"action":		"$N����һת��һ�С���Ы��β����$w�ڿ���ת�˸�Ȧ���Թ���ĽǶ�����$n",
	"force":		120,
	"dodge":		-20,
	"damage":		40,
	"lvl" : 10,
	"skill_name" : "��Ы��β",
	"damage_type":	"����"
]),
([	"action":		"$Nһ�����ޣ�һ�С�������˿��������$w����������Ӱ������$n",
	"force":		180,
	"dodge":		-30,
	"damage":		50,
	"lvl" : 20,
	"skill_name" : "������˿",
	"damage_type":	"����"
]),
([	"action":		"$N������ң�һ�С���ܳ�����������$w������ң�ֱ����$n�ؿ�",
	"force":		240,
	"dodge":		-10,
	"damage":		60,
	"lvl" : 30,
	"skill_name" : "��ܳ���",
	"damage_type":	"����"
]),
([	"action":		"$N��������һ�С���򼷭��������$wת��������ȦȦ������һ�����磬ֱ��$n��ȥ",
	"force":		300,
	"dodge":		-20,
	"damage":		80,
	"lvl" : 40,
	"skill_name" : "��򼷭��",
	"damage_type":	"����"
])

});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if( (int)me->query_skill("wudu-xinfa") < 25 )
		return notify_fail("����嶾�ķ�̫�ͣ�����������޷���\n");

	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("���������һ�����Ӳ���������޷���\n");

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
//	����������
        mapping a_action;
        int i, level;
	string *sanwu_msg = 
	({
		"$Nһ��"+WHT"���޿ײ��롹"+NOR"��$n��ǰ���ᶼ��$w��Ӱ��ͬʱ��$nȫ�������Ѩ",
		"$Nһ��δ�����ڶ���"+WHT"������������"+NOR"��Ȼ�򵽣�����$w����$n�����ƫ��Ѩ��",
		WHT"����ɨ��$N����һ�С�������Ϊ����$w����������ר��$n��������֮��"NOR,
	});
        level   = (int) me->query_skill("jueqing-bian", 1);

		if ( me->query_temp("sanwu") > 0 && me->query_temp("sanwu") <= 3 )
		{
			return ([
			"action": sanwu_msg[me->query_temp("sanwu")-1],
			"dodge": -200,
			"parry": -225,
			"force": 400,
			"damage": 100,
			"damage_type": "����",
			"post_action": (: sanwu :) ]);
		}

	        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                {
                        a_action = action[NewRandom(i, 20, level / 5)];
                        break;
                }
        a_action["force"] += level / 10;
        a_action["dodge"] -= level / 10;
        a_action["parry"] = level / 10;
        a_action["damage"] += level / 10;
        return a_action;
}
int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("��ľ�������������޷���\n");
        me->receive_damage("jingli", 25, "����͸֧�������ˡ�");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jueqing-bian/" + action;
}

int sanwu(object me, object victim, object weapon, int damage)
{
//	if( damage > 0 && me->query_temp("sanwu") ) 
//		me->delete_temp("sanwu");
}
mapping *query_skilldbase() {return action;}
