// Created by Lonely@nitan(1)

#include <ansi.h>
inherit F_CLEAN_UP;
int main(object me, string arg)
{
        string htsx;
        int jnd;

        if (! arg || sscanf(arg, "%s %d", htsx, jnd) != 2) 
                return notify_fail("ָ���ʽ��allocate <��������> <���ܵ���>\n"); 

        if ((int)me->query("points") < 1)
                return notify_fail("�������Ŀǰû��ʣ���κεļ��ܵ������������䣡\n"); 

        if (htsx != "����" && htsx != "����" && htsx != "����" && htsx != "��"
                && htsx != "str" && htsx != "int" && htsx != "con" && htsx != "dex") 
                return notify_fail("��ֻ���Խ����ܵ���䵽���������ԡ����Ǻ����������츳�����ϣ�\n"); 

        if (jnd < 1) return notify_fail("���ܵ����ķ���ÿ������Ҫ���ǣ��㡣\n");

        if (jnd > (int)me->query("points"))
                return notify_fail("��û����ô��ļ��ܵ�����\n"); 

        switch (htsx)
        {
        case "����": 
        case "str":
                  me->add("improve/str", jnd);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "����" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        case "����":
        case "int":
               me->add("improve/int", jnd);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "����" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        case "����":  
        case "con":  
                me->add("improve/con", jnd);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "����" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        case "��":
        case "dex":
                me->add("improve/dex", jnd);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "��" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        default:  
                return notify_fail("ָ���ʽ��allocate <��������> <���ܵ���>\n");
                break;
        }
        me->add("points", -jnd);

        tell_object(me, HIG "��Ŀǰ���� " + chinese_number(me->query("points")) + " �㼼�ܵ���û�з��䣡\n\n" NOR);
        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��allocate <��������> <���ܵ���>

HELP
        );
        return 1;
}                   

