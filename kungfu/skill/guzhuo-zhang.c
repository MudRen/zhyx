inherit SKILL;
#include <ansi.h>

mapping *action = ({
([	"action" : "$N一声大喝，左掌叠于右掌之上，劈向$n",
	  "force" : 320,
    "attack": 130,
	  "dodge" : 90,
    "parry" : 100,
   	"damage": 90,
	  "lvl"   : 0,
	"damage_type" : "内伤"
]),
([	"action" : "$N面色凝重，双掌轻抖，飘忽不定地拍向$n",
	  "force" : 350,
    "attack": 140,
	  "dodge" : 100,
    "parry" : 110,
	  "damage": 95,
	  "lvl"   : 50,
   	"damage_type" : "内伤"
]),
([	"action" : "$N沉身顿气，贯出双掌，顿时只见一片掌影攻向$n",
	"force" : 380,
        "attack": 150,
	"dodge" : 110,
        "parry" : 120,
	"damage": 100,
	"lvl"   : 100,
	"damage_type" : "内伤"
]),
([	"action" : "$N双掌平挥，猛击向$n的$l，毫无半点花巧可言",
	"force" : 410,
        "attack": 160,
	"dodge" : 110,
        "parry" : 120,
	"damage": 110,
	"lvl"   : 150,
        "damage_type" : "内伤"
]),
([	"action" : "$N体内真气迸发，双掌缤纷拍出，顿时一片掌影笼罩$n",
	"force" : 440,
        "attack": 170,
	"dodge" : 120,
        "parry" : 130,
	"damage": 120,
	"lvl"   : 180,
	"damage_type" : "内伤"
]),
([	"action" : "$N左掌虚晃，右掌携着千钧之力猛然向$n的头部击落",
	"force" : 460,
        "attack": 180,
	"dodge" : 130,
	"damage": 130,
        "parry" : 130,
	"lvl"   : 220,
        "damage_type" : "内伤"
]),
([	"action" : "$N身子蓦的横移，右手横扫$n的$l，左手攻向$n的胸口",
	"force" : 500,
        "attack": 190,
	"dodge" : 140,
        "parry" : 140,
	"damage": 140,
	"lvl"   : 260,
        "damage_type" : "内伤"
]),
([	"action" : "$N陡然一声暴喝，真气迸发，双掌同时击向$n的$l",
	"force" : 550,
        "attack": 200,
	"dodge" : 150,
        "parry" : 150,
	"damage": 150,
	"lvl"   : 300,
        "damage_type" : "内伤"
])
});

int valid_enable(string usage)
{
	return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练古拙掌法必须空手。\n");

        if (me->query("str") < 26)
                return notify_fail("你先天膂力不足，无法学习淳厚的古拙掌法。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，无法练古拙掌法。\n");

	if ((int)me->query("max_neili") < 2500)
		return notify_fail("你的内力太弱，无法练古拙掌法。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法火候不够，无法练古拙掌法。\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guzhuo-zhang", 1))
		return notify_fail("你的基本掌法水平有限，无法领会更高深的古拙掌法。\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("guzhuo-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够练古拙掌法。\n");

	me->receive_damage("qi", 85);
	me->add("neili", -90);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus > 120 && (int)me->query_skill("xixing-dafa",1) > 300 && random(3)!=1) 	
        {
                victim->receive_wound("qi", (damage_bonus - 110) / 2, me);
                me->add("qi", (damage_bonus - 110) / 2);
                if (me->query("qi") > me->query("eff_qi"))
                	me->set("qi", me->query("eff_qi") );  
                return MAG "只听“哧”的一声" + victim->name() + MAG "面如枯槁，真元已被"+me->name()+MAG"所吸！"+me->name()+MAG"的面容又红润了些。\n" NOR;
        }
}

string perform_action_file(string action)
{
	return __DIR__"guzhuo-zhang/" + action;
}
