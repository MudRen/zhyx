inherit SKILL;

mapping *action = ({
([      "action":"$N使一式「力破天下」，手中$w由左至右横扫向向$n的$l",
        "force" : 130,
        "parry" : 30,
        "dodge" : 50,
	    "attack": 100,
        "damage": 100,
        "lvl"   : 0,
        "skill_name" : "力破天下",
        "damage_type":  "割伤"
]),
([      "action":"$N踏上一步，「寒魄式」，手中$w盘旋飞舞出一道金光劈向$n的$l",
        "force" : 150,
        "parry" : 40,
        "dodge" : 60,
	 "attack": 110,
        "damage": 110,
        "lvl"   : 30,
        "skill_name" : "寒魄式",
        "damage_type":  "割伤"
]),
([      "action":"$N手中$w一抖，一招「天降式」，斜斜反腕撩出，攻向$n的$l",
        "force" : 170,
        "parry" : 50,
        "dodge" : 70,
	 "attack": 120,
        "damage": 120,
        "lvl"   : 50,
        "skill_name" : "天降式",
        "damage_type":  "割伤"
]),
([      "action":"$N手中$w连绕数个大圈，一式「龙舞九天」，一道光飞向$n的$l",
        "force" : 190,
        "parry" : 60,
        "dodge" : 80,
        "damage": 130,
	 "attack": 130,
        "lvl"   : 70,
        "skill_name" : "龙舞九天",
        "damage_type":  "刺伤"
]),
([      "action":"$N手中$w斜指苍天，一式「天罡式」，对准$n的$l斜斜击出",
        "force" : 220,
        "parry" : 70,
        "dodge" : 90,
        "damage": 140,
	    "attack": 140,
        "lvl"   : 90,
        "skill_name" : "天罡式",
        "damage_type":  "刺伤"
]),
([      "action":"$N一式「冷兵出鞘」，$w飞斩盘旋，如疾电般射向$n的胸口",
        "force" : 250,
        "parry" : 80,
        "dodge" : 100,
	    "attack": 150,
        "damage": 150,
        "lvl"   : 110,
        "skill_name" : "冷兵出鞘",
        "damage_type":  "刺伤"
]),
([      "action":"$N手中$w一沉，一式「破光式」，无声无息地滑向$n的$l",
        "force" : 270,
        "parry" : 90,
        "dodge" : 110,
        "damage": 160,
	    "attack": 160,
        "lvl"   : 130,
        "skill_name" : "破光式",
        "damage_type":  "刺伤"
]),
([      "action":"$N手中$w斜指苍天，剑芒吞吐，一式「天孤冷月式」，对准$n的$l斜斜击出",
        "force" : 300,
        "parry" : 100,
        "dodge" : 120,
        "damage": 170,
	    "attack": 170,
        "lvl"   : 150,
        "skill_name" : "天孤冷月式",
        "damage_type":  "刺伤"
]),
([      "action":"$N左指凌空虚点，右手$w逼出丈许雪亮光芒，一式「剑气纵横」刺向$n的咽喉",
        "force" : 310,
        "parry" : 110,
        "dodge" : 130,
	     "attack": 180,
        "damage": 180,
        "lvl"   : 170,
        "skill_name" : "剑气纵横",
        "damage_type":  "刺伤"
]),
([      "action":"$N合掌跌坐，一式「破阳无极」，$w自怀中跃出，如疾电般射向$n的胸口",
        "force" : 350,
        "parry" : 120,
        "dodge" : 140,
        "damage": 200,
	    "attack": 200,
        "lvl"   : 290,
        "skill_name" : "破阳无极",
        "damage_type":  "刺伤"
])
});

int valid_enable(string usage)
{ 
       return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;
        int lv = me->query_skill("poyang-jian", 1);

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，不能学习破阳冷光剑。\n");

        if (me->query("max_neili") < 1500)
                return notify_fail("你的内力修为不够，不能学习破阳冷光剑。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候不够，不能学习破阳冷光剑。\n");

        if ((int)me->query_skill("sword", 1) < lv)
                return notify_fail("你的基本剑法水平有限，无法领会更高深的破阳冷光剑。\n");
       
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
        level = (int) me->query_skill("poyang-jian", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("你的体力不够练破阳冷光剑。\n");

        if ((int)me->query("neili") < 130)
                return notify_fail("你的内力不够练破阳冷光剑。\n");

        me->receive_damage("qi", 75);
        me->add("neili", -70);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poyang-jian/" + action;
}