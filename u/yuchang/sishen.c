// sishen.c  不哭死神

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return CYN "不哭死神" NOR; }

int perform(object me, string skill)
{
        return notify_fail("不哭死神这项技能不需要运用。\n");
}

