// xuedao-daofa.c 血刀
// updated by lwx 

inherit SKILL;
#include <ansi.h> 

string *action_msg = ({
        "$N使出一招"HIW"「磨牙吮血」"NOR"，把刀咬在口中，只在$n身前身后乱转，瞅个破绽，猛地欺身向前，拔出刀来一刀直劈下去",
        "$N腰劲运肩，肩通於臂，向前一冲，跨出一步半，攸忽缩脚，身形一矮向$n下三路实砍两刀，正是一招"HIB"「批纸削腐」"NOR,
        "$N口发荷荷怪声，手中刀直向前伸，一招"HIR"「血海茫茫」"NOR"，手中$w直向前伸，将$n的两肩和面门笼罩在刀光之下",
        "$N手一扬，一招"HIC"「流星经天」"NOR"，手中刀脱手飞出，一溜红光，径向$n的$l飞去",
        "$N一招"HIG"「血踪万里」"NOR"，身子原地打了一个转, 反手一刀向$n的$l捅了过去",
        "$N双手反执刀尖，合於怀中，突然左肩微沉，一招"HIC"「偷云换日」"NOR"，左手从右臂下穿出转移$n的目光，右手执刀猛刺$n的$l",
        "$N突然还刀入鞘，蓦地欺近身去，身体半跪，反手抽刀，一式"HIY"「血洗天河」"NOR"，只见一片匹练也似的刀光从$n下阴直撩至天灵盖",
        "$N刀尖平指，一招"HIM"「血流漫面」"NOR"，刀光霍霍，三横两直，带着阵阵风声砍向$n的面门",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query("character") == "光明磊落")
                return notify_fail("你心中暗道：这血刀大法邪气太重，甚过诡异，莫" 
                                   "不是专门设来害人的？\n");

        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("xuehai-mogong", 1) < 20)
                return notify_fail("你的血海魔功火候太浅。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(30), 
                "attack": 70 + random(10),
                "dodge" : 70 + random(10),
                "parry" : 70 + random(10),
                "damage_type": random(2) ? "挫伤" : "割伤", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        ||  (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 40)
                return notify_fail("你的体力不够练血刀刀法。\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("你的内力不够练血刀刀法。\n");
        me->receive_damage("qi", 30);
        me->add("neili", -20);
        return 1;
} 
mixed hit_ob(object me, object victim, int damage) 
{
        mixed result;
        if (damage < 100) return 0; 
        if (random(damage / 2) > victim->query_str()) 
        { 
                result = ([ "damage": damage ]);
                result += (["msg" : HIW "$N邪气大发，顿时光芒大胜。挥着大刀向着$n身上挥来，$n" BLINK + 
                                    HIR "鲜血" NOR + HIW "狂喷而出！\n" NOR ]);
                return result;
        } 
}
string perform_action_file(string action)
{
        return __DIR__"xuedao-daofa/" + action;
}

