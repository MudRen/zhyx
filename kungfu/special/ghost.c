// guimai.c ��������

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ǧ��һ�������⾭��������������\n"
                           "�������˾�����Ӥ����������Ϊ������\n"
                           "��ҽ�������䷨����������ز�ۡ�����\n"
                           "������겻���ߣ��˺����������ڹ�����\n"
                           "�빦����������Ů������ֱ��������а��\n"
                           "�����ǿ���ħ�������������Թ���\n");
}
