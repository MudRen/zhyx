// sishen.c  ��������

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return CYN "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������������ܲ���Ҫ���á�\n");
}

