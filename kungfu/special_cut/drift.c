// xunying.c ��Ӱ����

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "��Ӱ����" NOR; }

int perform(object me, string skill)
{
        return notify_fail("���ڽ���������ݹ����󣬲����������\n"
                           "��������أ�������̬�����۵ס��˺�\n"
                           "�����ܵ�����ж��֮�����Ի�\n");
}
