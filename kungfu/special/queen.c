// queen.c  ������Ů

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "������Ů" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������Ů����ܲ���Ҫ���á�\n");
}

