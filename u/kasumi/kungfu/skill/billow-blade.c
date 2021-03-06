
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N突然使出一招「大浪掏沙」，手中$w掀起滔天巨浪直劈$n的$l",
        "skill_name" : "大浪掏沙",
        "force"  : 300,
        "attack" : 100,
        "dodge"  : 80,
        "parry"  : 100,
        "lvl"    : 0,
        "damage" : 110,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出一招「推波助澜」掌中$w缓缓推动，重重的横削$n的$l",
        "skill_name" : "推波助澜",
        "force"  : 340,
        "attack" : 120,
        "dodge"  : 100,
        "parry"  : 110,
        "lvl"    : 50,
        "damage" : 120,
        "damage_type" : "割伤",
]),
([      "action" : "$N身形一矮，一招「钱江秋涛」，$w往$n的$l斜斜撩出一刀",
        "skill_name" : "钱江秋涛",
        "force"  : 380,
        "attack" : 130,
        "dodge"  : 110,
        "parry"  : 120,
        "lvl"    : 100,
        "damage" : 130,
        "damage_type" : "割伤",
]),
([      "action" : "$N凌空一跃，直落一刀「拨浪一击」，$w狠狠的砍向$n的$l",
        "skill_name" : "拨浪一击",
        "force"  : 420,
        "attack" : 140,
        "dodge"  : 120,
        "parry"  : 130,
        "lvl"    : 150,
        "damage" : 140,
        "damage_type" : "割伤",
]),
([      "action" : "$N手中$w刀光泛白，一招「滴翠匀碧」，无声无息地斩向$n的$l",
        "skill_name" : "滴翠匀碧",
        "force"  : 460,
        "attack" : 150,
        "dodge"  : 130,
        "parry"  : 140,
        "lvl"    : 200,
        "damage" : 150,
        "damage_type" : "割伤",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_neili") < 5000 )
                return notify_fail("你的内力不够，没有办法练沧浪刀法。\n");
               
        if (me->query("dex") < 34)
                return notify_fail("你先天身法不足，难以练习沧浪刀法。\n");       

        if ((int)me->query_skill("force") < 400)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < 200)
                return notify_fail("你的基本刀法火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("billow-blade",1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的沧浪刀法。\n");
                
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
        level   = (int) me->query_skill("hujia-daofa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}



int practice_skill(object me)
{ 
        object weapon;
        

        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "blade" )
                return notify_fail("你必须先找一把刀，才能练刀法。\n");
                
         if ((int)me->query("qi") < 200)
                return notify_fail("你的体力不够，练不了沧浪刀法。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你的内力不够，练不了沧浪刀法。\n");

        me->receive_damage("qi", 200);
        me->add("neili", -300);      

        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"billow-blade/" + action;
}


