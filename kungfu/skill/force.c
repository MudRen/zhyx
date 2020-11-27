// force.c

#include <ansi.h>

inherit SKILL;


int valid_learn(object me)
{
        int lv = me->query_skill("force", 1);

        if (me->query_skill("dodge", 1) < lv
           || me->query_skill("parry", 1) < lv)
                return notify_fail("������Ṧ������мܻ���㣬�޷������о�"
                                   "�����ڹ���\n");

        return 1;
}

string exert_function_file(string func)
{
        return "/kungfu/skill/force/" + func;
}

void skill_improved(object me)
{
}
