// dispel.c

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "�����Ե" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ʱ���Ե�ɺϣ����ɷ���������\n"
                           "���ç����򣬴Ӵ�֮��ٶ����֡�\n");
}

