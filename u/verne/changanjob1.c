// changanjob.c  �����ĳ�����������������ָ��

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me)
{        
        mapping q;
        int time1, time2;
        if ( me->query("cajb_total_ask/time") )
        {
           time1 = ( time() - me->query("cajb_total_ask/time") ) / 3600;
           time2 = (( time() - me->query("cajb_total_ask/time") ) % 3600 )/60;
           if (time2 < 0) time2 = 0;
           if ( time1 > 0 )
           {
             write("����һ�ֳ���������" + time1 + "Сʱ" + time2 +
                   "����ǰ��ʼ���ġ�\n");
           }  else
           {
             write("����һ�ֳ���������" + time2 + "����ǰ��ʼ���ġ�\n");
           }
        }

        if (me->query("changanjob_count"))
        write(sprintf("���Ѿ���������� %d �����������񣬼�������Ŭ������\n",
                     me->query("changanjob_count")));

        if (! mapp(q = me->query("changanjob")))        
        return notify_fail("������û����ȡ������������\n");             

        q =  me->query("changanjob");

                switch (q["kind"])
        {

           case "whisper":
                write("Ŀǰ֪������ȥ��һ�����Ŵ���"HIY +
                q["place"] + NOR "��" HIY +  q["target"]
                + NOR"��\n");
                return 1;

           case "patrol":                
                write("Ŀǰ֪������ȥ��������Ѳ�ǡ�\n");
                return 1;

           case "hunt":                
                write("Ŀǰ֪������ȥ��������ɱҰ�ޱ������ա�\n");
                return 1;  
        }

        write("������û����ȡ������������\n");
        return 1;
}



int help(object me)
{
        write(@HELP
���ָ�����������������ɳ���������������
HELP );
        return 1;
}

