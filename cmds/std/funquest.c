// funquest.c  ������Ȥζ������������ָ��

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me)
{
        object ob;
        mapping q;
        int time1, time2;
        if ( me->query("xquest_total_ask/time") )
        {
           time1 = ( time() - me->query("xquest_total_ask/time") ) / 3600;
           time2 = (( time() - me->query("xquest_total_ask/time") ) % 3600 )/60;
           if (time2 < 0) time2 = 0;
           if ( time1 > 0 )
           {
             write("����һ��Ȥζ������" + time1 + "Сʱ" + time2 +
                   "����ǰ��ʼ���ġ�\n");
           }  else
           {
             write("����һ��Ȥζ������" + time2 + "����ǰ��ʼ���ġ�\n");
           }
        }
        if (me->query("xquest_count"))
        write(sprintf("���Ѿ���������� %d ��Ȥζ���񣬼�������Ŭ������\n",
                     me->query("xquest_count")));

        if (! mapp(q = me->query("xquest")))
        {
                write("������û�����κ�Ȥζ����\n");
                return 1;
        }


        q =  me->query("xquest");

                switch (q["kind"])
        {

        case 0:
                write("Ŀǰ"HIY + q["init_npc"] + NOR"����ȥ��" + q["place"] +
                "��"HIY + q["target_npc"] + NOR"����������\n");
                return 1;

        case "send_letter":
                write("Ŀǰ"HIY + q["init_npc"] + NOR"�����һ���Ž���"HIY +
                q["place"] + NOR "��" HIY +  q["target_npc"]
                + NOR"���\n");
                return 1;

        case "bring_receipt":
                write("Ŀǰ"HIY + q["init_npc"] + NOR"����ѻ�ִ���ظ�"HIY +
                q["target_npc"]+ NOR"��\n");
                return 1;

        case "buy_thing":
                write("Ŀǰ"HIY + q["init_npc"] + NOR"�������ȥ��" +
                q["item"]+ "��\n");
                return 1;      
     /*   case "buy_thing":
             write("Ŀǰ"HIY + q["init_npc"] + NOR"�������ȥ��һ��������\n");
             return 1; */

        case "take_npc":
                write("Ŀǰ"HIY + q["init_npc"] + NOR"���������Զ������"HIY +
                q["target_npc"]+ NOR"��ȥ"HIY + q["place1"] + NOR"��" HIY +
                q["place2"] + NOR"��\n");
                return 1;

        case "pay_gold":
                write("Ŀǰ"HIY + q["init_npc"] + NOR"���㸶����"HIY +
                chinese_number(q["pay_amount"])+ NOR"��������������\n");
                return 1;

        case "do_drawing":
                write("Ŀǰ" HIY + q["init_npc"] + NOR"�����һ��������"HIY +
                q["place1"] + NOR "��" HIY +  q["place2"] + NOR "ȥ���ٰ�����"
                "�ĵ��λ�������������\n");
                return 1;
        case "guess_riddle":
                write("Ŀǰ"HIY + q["init_npc"] + NOR"����¸�����:" HIG +
                q["riddle"]+ NOR"�������������ڻش�\n");
                return 1;

        }

        write("������û�����κ�Ȥζ����\n");
        return 1;
}



int help(object me)
{
        write(@HELP
ָ���ʽ : xquest  ���ָ������������������Ȥζ����������
HELP );
        return 1;
}

