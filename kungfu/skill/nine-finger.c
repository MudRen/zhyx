// nine-finger.c
// 华夏玩家mfox的自创武功：九字真言手印
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "mfox";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "不动根本印",
        "action":  "只见$N两手高举过头，紧扣如莲花，无名指斜起，正是『不动根本印』，\n"
                   "身形屹立如山，完全不为$n所动",
        "dodge" : 90,
        "damage": 200,
        "force" : 350,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "大金刚轮印",
        "action":  "只见$N双手合什，饱满如轮，使出『大金刚轮印』，森森拳风无坚不摧般地击向$n",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "外狮子印",
        "action":  "只见$N左手抱拳，右手外反，正是『外狮子印』，\n"
                   "双拳不住变化，在$n面前闪出无数手印，令$n一时不知所措",
        "dodge" : 95,
        "damage": 210,
        "force" : 360,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "内狮子印",
        "action":  "只见$N右掌直立胸前，左手内收，正是『内狮子印』，\n"
                   "从一个意想不到的角度突然一拳击向$n的$l",
        "dodge" : 105,
        "damage": 220,
        "force" : 370,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "外缚印",
        "action":  "只见$N作出连串印结，变化无方，正是『外缚印』，完全将$n笼罩在双掌之下",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "因风离海上",
        "action":  "只见$N左掌立于胸前，右手暗捏印诀缓缓推出，正是『内缚印』，\n"
                   "向$n的$l击了过去，令$n无从躲闪",
        "dodge" : 115,
        "damage": 240,
        "force" : 390,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "智拳印",
        "action":  "只见$N双手轻摇，如鬼魅般欺至$n身前，双拳连续不断击向$n的$l，\n"
                   "瞬间变化出百多种印变，正是『智拳印』",
        "dodge" : 115,
        "damage": 260,
        "force" : 410,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "日轮印",
        "action":  "只见$N往前冲出，似扑非扑，若缓若急，一招『日轮印』，\n"
                   "长生诀真气如旭日初生般连绵不绝向$n扑面涌去，令人顿有退避之意。",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "宝瓶印",
        "action":  "只见$N身形凌空飞起，双手暗捏『宝瓶印』，\n"
                   "拳风暗含螺旋真气，隐带风雷之音，从空中当头向$n连续击出。",
        "dodge" : 115,
        "damage": 300,
        "force" : 450,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练九字真言手印。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练九字真言手印。\n");

    if( (ob = me->query_temp("weapon")) || 
        (ob = me->query_temp("handing")) )
        return notify_fail("你只有空着双手才能修炼指法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="finger" || usage=="parry";
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
    level   = (int) me->query_skill("nine-finger",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习九字真言手印。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习九字真言手印。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"nine-finger/" + action;
}
