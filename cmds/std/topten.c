// toptenadd.c
#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string str,*astr,type;
        int i;
        mapping paiming;

        seteuid(geteuid(me));
        if (!arg||arg=="")
                  return notify_fail("ָ���ʽ : topten ��������
Ŀǰ�����������У�\n
        ��"+LOCAL_MUD_NAME()+"��ʮ��������а�gaoshou��
        ��"+LOCAL_MUD_NAME()+"��ʮ�������а�exp��
        ��"+LOCAL_MUD_NAME()+"��ʮ�������а�richman��
        ��"+LOCAL_MUD_NAME()+"��ʮ��ħͷ���а�motou��
        ��"+LOCAL_MUD_NAME()+"��ʮ���������а�laoshou��
        ��"+LOCAL_MUD_NAME()+"��ʮ�����������а�beiqing��\n");
        if (arg=="gaoshou")
              type="gaoshou";
        else if(arg=="exp")
              type="exp";
        else if(arg=="richman"||arg=="rich")
              type="rich";
        else if(arg=="motou"||arg=="pker")
              type="pker";
        else if(arg=="laoshou"||arg=="age")
              type="age";
        else if(arg=="beiqing"||arg=="killed")
              type="killed";
        else 
              type=arg;
        if (type == "gaoshou")
        {
                paiming = BIWU_D->get_list();
                str = HIC "      *          ��       ��       ��       ��          *\n"NOR;
                str += HIC "-------------------------------------------------------------\n";
                str += "\n";
                for (i = 0;i < sizeof(paiming);i++)
                {
                        str += HIY + "   �����µ�" + chinese_number(i+1) + "�� " + NOR + 
                               paiming[i]["title"] + "\n";
                        str += "\n";
                }
                str += HIC "-------------------------------------------------------------\n";
        } else str=TOPTEN_D->topten_query(type);
        write(str+"\n");
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : topten ��������
Ŀǰ������������:
gaoshou  ʮ�����
exp      ʮ����
richman  ʮ����
motou    ʮ��ħͷ
laoshou  ʮ������
beiqing  ʮ��������
HELP
    );
    return 1;
}

