#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);
int main(object me, string arg)
{
        int nowtime = time();
        mapping quest;
        if(!(quest =  me->query("quest"))) {
               write("������û���κ�����\n");
               if ( me->query("fail_time") )
                       write("��������һ������ʧ�ܣ��Ѿ�" + time_period(time()-me->query("fail_time")) + "�ˡ�\n");
               return 1;
               }
               
        write("�����ڵ�������" + quest["type"] + quest["quest"] + "��\n"
);
        nowtime = quest["task_time"] - time();
        if( nowtime  > 0 )
                write("�㻹��" + time_period(nowtime) + "ȥ�������\n");
        else
                write("�������Ѿ�û���㹻��ʱ����������ˡ�\n");
 
        return 1;
}
string time_period(int timep)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;
 
        if(d) time = chinese_number(d) + "��";
        else time = "";
 
        if(h) time += chinese_number(h) + "Сʱ";
        if(m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��";

        return time;
}
 
int help(object me)
{
        write(@HELP
ָ���ʽ : renwu ���ָ�������ʾ���㵱ǰ������
HELP
        );
        return 1;
}

