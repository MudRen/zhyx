#include <ansi.h>
int main(object me, string str)
{
        string output;
        me->add("sen",-5);
        output = HIG"        ������ɽׯʹ�����\n" NOR;
        output += "������������������������������������������������������\n\n";
        output += TASKD_D->dyn_quest_list();
        output += "������������������������������������������������������\n\n";

        output += HIY"��ʹ�����·���ʱ�仹��"+TASKD_D->check_time(me)+"��\n"NOR;
        me->start_more(output);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: task

���ָ����������֪����ɽׯĿǰ������ʹ����

HELP
        );
        return 1;
}


