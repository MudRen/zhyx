// force.c

#include <ansi.h>

inherit SKILL;


int valid_learn(object me)
{
        int lv = me->query_skill("force", 1);

        if (me->query_skill("dodge", 1) < lv
           || me->query_skill("parry", 1) < lv)
                return notify_fail("你基本轻功或基本招架火候不足，无法继续研究"
                                   "基本内功。\n");

        return 1;
}

string exert_function_file(string func)
{
        return "/kungfu/skill/force/" + func;
}

void skill_improved(object me)
{
}
