#include <ansi.h>
inherit SKILL;


mapping *action = ({
([      "action":"$N使一式「探海屠龙」，手中$w由左至右横扫向向$n的$l",
        "force" : 170,
        "attack": 100,
        "dodge" : 100,
        "damage": 130,
        "lvl" : 0,
        "skill_name" : "探海屠龙",
        "damage_type":  "割伤"
]),
([      "action":"$N手中$w斜指苍天，一式「横行漠北」，对准$n的$l斜斜击出",
        "force" : 200,
        "attack": 110,
        "dodge" : 120,
        "damage": 140,
        "lvl" : 80,
        "skill_name" : "横行漠北",
        "damage_type":  "刺伤"
]),
([      "action":"$N一式「马蹴落花」，手腕急抖，挥洒出万点金光，刺向$n的$l",
        "force" : 220,
        "attack": 130,
        "dodge" : 130,
        "damage": 150,
        "lvl" : 100,
        "skill_name" : "马蹴落花",
        "damage_type":  "刺伤"
]),
([      "action":"$N回剑自守，使一式「深藏若虚」，蓦地手中$w向$n击出",
        "force" : 300,
        "attack": 140,
        "dodge" : 120,
        "damage": 160,
        "lvl" : 180,
        "skill_name" : "深藏若虚",
        "damage_type":  "刺伤"
]),
([      "action":"$N左足踢起，一式「魁星踢斗」，$w从不可思议的角度刺向$n",
        "force" : 340,
        "attack": 150,
        "dodge" : 130,
        "damage": 170,
        "lvl" : 200,
        "skill_name" : "魁星踢斗",
        "damage_type":  "刺伤"
]),
([      "action":"$N一式「紫电穿云」，$w突然从天而降，一片金光围掠$n全身",
        "force" : 380,
        "attack": 160,
        "dodge" : 140,
        "damage": 180,
        "lvl" : 220,
        "skill_name" : "紫电穿云",
        "damage_type":  "刺伤"
])
});

int valid_enable(string usage)
{
	return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不足，无法学习全真剑法。\n");

        if (me->query("max_neili") < 1000)
                return notify_fail("你的内力修为太差，无法学习全真剑法。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法修为不够，无法学习全真剑法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("quanzhen-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的全真剑法。\n");

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
        level = (int) me->query_skill("quanzhen-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
	    string wn;
		object weapon;
		int lvl;

		weapon = me->query_temp("weapon");
		wn = weapon->name();
		lvl = me->query_skill("yunv-xinjing", 1);

        if (lvl < 150
            || me->query("neili") < 300
            || ! objectp(weapon = me->query_temp("weapon"))            
            || ! me->query("can_learn/yunv-xinjing/wall")
			|| random(5) < 1 )
                return 0;

        if ((string)weapon->query("skill_type") == "sword"
            && me->query_skill_mapped("sword") == "quanzhen-jian")
        {
                damage_bonus = lvl + random(lvl / 2 );

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);
				return HIG ""+ me->name() + HIG "手中" + wn + HIG "忽的一振，将玉"
                       "女心经功力运于剑端，全真剑法发挥得淋漓尽致。\n" NOR; 
                
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp;
        object weapon1, weapon2;

        if (me->query_skill_mapped("sword") == "suxin-jian" && me->query_skill_mapped("parry") != "quanzhen-jian")
		return;
		
		if (me->query_skill_mapped("sword") == "quanzhen-jian" && me->query_skill_mapped("parry") != "suxin-jian")
		return;
		
		if (!(weapon1 = me->query_temp("weapon"))
           ||!( weapon2 = me->query_temp("handing"))
           || ! living(me))
        return;
        
        ap = ob->query_skill("parry");
        dp = me->query_skill("parry", 1) / 2 + (me->query_skill("quanzhen-jian", 1) + me->query_skill("suxin-jian", 1))/2;       
             if (ap / 2 + random(ap) < dp)
             {
                        result = ([ "damage": -damage ]);
                        result += (["msg" : MAG "$n" MAG "双剑纷飞，招式中所有破绽都为另一剑补去，架开了$N" MAG "的攻势。\n" NOR]);                                           
                       
             }             
             return result;
             
}


int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("你的体力不够练全真剑法。\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够练全真剑法。\n");

        me->receive_damage("qi", 55);
        me->add("neili", -53);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"quanzhen-jian/" + action;
}
