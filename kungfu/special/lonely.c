// lonely.c  ��ɷ����

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return CYN "��ɷ����" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ɷ��������ܲ���Ҫ���á�\n");
}

