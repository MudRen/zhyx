// yinshe-bianfa 银蛇鞭法 by kasumi

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([     "action":   "$N身形不动，一招「飞蛇夺珠」，手中$w直奔$n的双目而去",
       "dodge":        100,
       "parry":        80,
	   "attack":       100,
       "damage":       100,
       "force":        300,
       "lvl" : 0,
       "skill_name" : "飞蛇夺珠",
       "damage_type":  "刺伤"
]),
([     "action":   "$N一招「攀蛇附凤」，手中$w如影附形，向$n的颈部卷去",
       "dodge":     110,
       "parry":     90,
	   "attack":    110,
       "damage":    120,
       "force":     340,
       "lvl" : 40,
       "skill_name" : "攀蛇附凤",
       "damage_type":  "瘀伤"
]),
([     "action":   "$N突然反身后退，待$n迫近时，反手一招「神蛇摆尾」，手中$w如离弦之箭，直奔$n的前胸而去",
       "dodge":     120,
       "parry":     100,
	   "attack":    120,
       "damage":    140,
       "force":     380,
       "lvl" : 80,
       "skill_name" : "神蛇摆尾",
       "damage_type":  "刺伤"
]),
([     "action":   "$N猛地一抖，手中$w化出无数圆环，一招「乌蛇绞柱」，圈向$n的上身",
       "dodge":     130,
       "parry":     100,
	   "attack":    130,
       "damage":    160,
       "force":     420,
       "lvl" : 120,
       "skill_name" : "乌蛇绞柱",
       "damage_type":  "瘀伤"
]),
([     "action":  "$N身形拔起，力贯鞭梢，一招「天蛇下凡」，手中$w晃出无数鞭影，朝$n迎头击下",
       "dodge":    140,
       "parry":    100,
       "damage":   180,
	   "attack":   140,
       "force":    440,
       "lvl" : 160,
       "skill_name" : "天蛇下凡",
       "damage_type":  "瘀伤"
]),
([     "action":  "$N忽地就地一滚，一招「地蛇打滚」，手中$w以迅雷不及掩耳之势扫向$n的双腿",
       "dodge":    150,
       "parry":    100,
	   "attack":   150,
       "damage":   200,
       "force":    480,
       "lvl" : 200,
       "skill_name" : "地蛇打滚",
       "damage_type":  "瘀伤"
]),
([     "action": "$N身形伏低，一招「游蛇归巢」，手中$w抖出无数鞭影，对准$n的下身攻去",
       "dodge":   160,
       "parry":   110,
       "damage":  220,
	   "attack":  160,
       "force":   520,
       "lvl" : 240,
       "skill_name" : "游蛇归巢",
       "damage_type":  "瘀伤"
]),
([     "action": "$N猛地抖直手中的$w，一招「金蛇出海」，沿着$n的脚跟直撩而上，直奔$n的头部而去",
       "dodge":   160,
       "parry":   120,
	   "attack":  170,
       "damage":  240,
       "force":   560,
       "lvl" : 260,
       "skill_name" : "金蛇出海",
       "damage_type":  "瘀伤"
])
});
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 100 )
               return notify_fail("你的内力不足，无法练银蛇鞭法。\n");

	     if( (int)me->query_skill("xiuluo-yinshagong",1) < 180 )
               return notify_fail("你的修罗阴煞功等级不够，无法修炼银蛇鞭法。\n");


       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("你必须先找一条鞭子才能练鞭法。\n");
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
       level   = (int) me->query_skill("yinshe-bianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;
	   int cost;   

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("你使用的武器不对。\n");	      

        if ((int)me->query("qi") < 100)
                return notify_fail("你的体力太低了。\n");

        cost = me->query_skill("yinshe-bianfa", 1) / 3 + 80;

        if ((int)me->query("neili") < cost)
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 100);
        me->add("neili", -cost);
        return 1;
}

string perform_action_file(string action)
{
       return __DIR__"yinshe-bianfa/" + action;
}
