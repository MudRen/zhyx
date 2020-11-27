#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action" : "$N��"+HIM+"����"+NOR+"��$n��$l����һ��",
	"force"  : 200,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 0,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N��ת����"+HIG+"β�ͼ�"+NOR+"��׼$n��$lһ��",
	"force"  : 210,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 100,
	"skill_name" : "���ֵ�Ѩ",
	"damage_type":	"ҧ��",
]),
([	"action" : "$N������"+HIC+"����"+NOR+"��$n��$l�ݺݵ�һҧ",
	"force"  : 220,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 200,
	"skill_name" : "ǰհ����",
	"damage_type":	"ҧ��",
]),
([	"action" : "$N��"+HIW+"צ��"+NOR+"��$n��$lһץ",
	"force"  : 230,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 300,
	"skill_name" : "������Ӱ",
	"damage_type":	"ץ��",
]),
([	"action" : "$Ņ��"+HIR+"����"+NOR+"��$n��$lһ��",
	"force"  : 240,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 400,
	"skill_name" : "�޵и��",
	"damage_type":	"����",
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }      
int valid_learn(object me)
{
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
    level = (int)me->query_skill("puyaogedou", 1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
      return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    return 1;
}
string perform_action_file(string action)
{
	return __DIR__"puyaogedou/" + action;
}