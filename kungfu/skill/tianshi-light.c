#include <ansi.h>
inherit SKILL;
string *dodge_msg = ({
        HIW "$n����΢Ц����һλ�·�����ʹ��$N���������ڵأ���Ĥ�ݡ�\n" NOR ,
});
mapping *action = ({
([      "action": MAG "$N�ſ��������ĳ��һ������$nϯ��ȥ��" NOR ,
        "force" : 0,
        "dodge" : 0,
        "damage": 0,
        "lvl" : 0,
        "skill_name" : "��ʹ֮��",
        "damage_type":   "ʥ��֮��"
]),
});

int valid_enable(string usage) 
{ 
    return usage == "sword" || usage == "dodge" || usage == "unarmed" || usage == "parry" 
           || usage == "blade" || usage == "whip" || usage == "force" ;
}
string query_skill_name(int level)
{
        int i;
        return action[0]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;
        return action[0];
}
string query_dodge_msg(string limb)
{
        return dodge_msg[0];
}
int valid_learn(object me)
{   
    if ( ! wizardp(me))
        return notify_fail("����ʹ֮�����ֻ�����¶�ѧϰ��\n");
}
string perform_action_file(string action)
{
        return __DIR__"tianshi-light/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"tianshi-light/exert/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
    if ( ! userp (victim)) 
    if ( living (victim)) victim -> unconcious () ;
}

