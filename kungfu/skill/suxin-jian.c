#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「松下对弈」，$w自右向左挥一个大弧，刺向$n的$l",
        "force"  : 150,
        "attack" : 100,
        "dodge"  : 90,
        "parry"  : 90,
        "damage" : 100,
        "lvl"    : 40,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「小园艺菊」，手中$w迅疾向$n的下盘连点三点",
        "attack" : 120,
        "force"  : 180,
        "dodge"  : 100,
        "parry"  : 100,
        "damage" : 110,
        "lvl"    : 54,
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出「西窗夜话」，手中$w中宫直入，攻向$n的$l",
        "force"  : 200,
        "attack" : 140,
        "dodge"  : 110,
        "parry"  : 100,
        "damage" : 120,
        "lvl"    : 59,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「幽兰空谷」，$w看似随意地一挥，从$n不可思议的角度攻入",
        "force"  : 240,
        "attack" : 150,
        "dodge"  : 120,
        "parry"  : 110,
        "damage" : 130,
        "lvl"    : 94,
        "damage_type" : "刺伤"
]),
([      "action" : "$N错开脚步，手中$w突然从自己的肋下刺出，却是一招「琴心剑胆」",
        "force"  : 280,
        "attack" : 160,
        "dodge"  : 120,
        "parry"  : 120,
        "damage" : 140,
        "lvl"    : 112,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「皓腕玉镯」，手中$w刺点$n的手腕",
        "force"  : 300,
        "attack" : 160,
        "dodge"  : 130,
        "parry"  : 120,
        "damage" : 150,
        "lvl"    : 124,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「牡丹含泪」，$w绕出数个银圈，平平地向$n的$l卷去",
        "force"  : 340,
        "attack" : 170,
        "dodge"  : 140,
        "parry"  : 120,
        "damage" : 160,
        "lvl"    : 131,
        "damage_type" : "刺伤"
]),
([      "action" : "$N脸现黯然之色，随意一招「蒹葭苍苍」，$w刺向$n的$l",
        "force"  : 380,
        "attack" : 180,
        "dodge"  : 160,
        "parry"  : 140,
        "damage" : 200,
        "lvl"    : 178,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry"; 
}

int valid_learn(object me)
{
        object weapon;


        /*if ((int)me->query("str", 1) < 28)
                return notify_fail("你的先天臂力不够，无法学习玉女素心剑。\n");*/

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不到，无法学习玉女素心剑。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法水平太低，无法学习玉女素心剑。\n");

        if (me->query("max_neili") < 2000)
                return notify_fail("你的内力修为不够，不能学习玉女素心剑。\n");

        if (me->query_skill("sword", 1) < me->query_skill("suxin-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的玉女素心剑。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;  
        level = (int) me->query_skill("suxin-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

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
			|| random(5) < 2 )
                return 0;

        if ((string)weapon->query("skill_type") == "sword"
            && me->query_skill_mapped("sword") == "suxin-jian")
        {
                damage_bonus = lvl / 2 + random(lvl / 2);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);
				return HIW ""+ me->name() + HIW "手中" + wn + HIW "忽的一振，将玉"
                       "女心经功力运于剑端，玉女剑法发挥得淋漓尽致。\n" NOR; 
                
        }
}

int practice_skill(object me)
{
        object weapon;
		int cost;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

		cost = me->query_skill("suxin-jian", 1) / 3 + 40;

        if ((int)me->query("qi") < 75)
                return notify_fail("你的体力不够练玉女素心剑。\n");

        if ((int)me->query("neili") < cost)
                return notify_fail("你的内力不足以练玉女素心剑。\n");		 

        me->receive_damage("qi", 60);
        me->add("neili", -cost);

        return 1;
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


string perform_action_file(string action)
{
        return __DIR__"suxin-jian/" + action;
}
