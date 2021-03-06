#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "只见$N身形一挫，以青龙之型向$n缠绕过去",
        "dodge": 20,
        "parry": 20,
        "attack": 20,
        "force": 20,
        "damage_type":  "砸伤"
]),
});

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你已将这种劲力融入四象神功，不必再分开练习了。\n");
        
        if (me->query("int") < 30)
                return notify_fail("你的先天悟性不足，无法领会青龙破。\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("你的暗器技能不够娴熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("qinglong-po", 1))
                return notify_fail("你的基本暗器水平有限，难以体会更精妙的青龙破。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("qinglong-po", 1))
                return notify_fail("你的基本拳脚水平有限，难以爆发更强劲的青龙破。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "unarmed";
}

int practice_skill(object me)
{
	return notify_fail("青龙破只能通过参悟青龙卷来提高。\n");
}

string perform_action_file(string action)
{
        return __DIR__"qinglong-po/" + action;
}
