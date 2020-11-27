// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string fam;
        string *member;
        string id;
        object area, npc;
        string msg;
        int n, kaifa, money;
                
        if (me->is_busy()) return notify_fail("����æ���أ�\n");

        if (! stringp(fam = me->query("bunch/bunch_name")))
                return notify_fail("��û�м����κΰ�ᣬ�޷���������������̡�\n");
                
        if (! arrayp(member = BUNCH_D->query_areas(fam)))
        {
                write("���ڰ���" + fam + "û���κε��̡�\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(fam + "����û���κε��̡�\n");

        if (! arg)
        {
                msg = sprintf(HIC "\n%-16s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR,
                      "��������", "פ�أΣУ�", "�ʽ��", "������",
                      "�ʲ����ƽ�", "�������루������", "�ҳ϶�");
                      
                msg += HIY "������������������������������������������������������������������������������������������\n" NOR;
                
                n = 0;
                foreach (id in member)
                {
                        area = get_object(id);
                        if (! objectp(area))
                                continue;
                                
                        if (! area->query("area/ziyuan"))
                                continue;
                
                        // npc = get_object(area->query("bunch/npc_file"));
                
                        n++;
                        msg += sprintf(HIC "%-16s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR, 
                               area->short(), area->query("bunch/npc_name") + "(" + area->query("bunch/npc_id") + ")",
                               area->query("bunch/jizhi") + "%", area->query("bunch/kaifa") + "%",
                               area->query("bunch/money") / 10000 + " ��", 
                               area->query("bunch/last_money") / 100 + " ��",
                               area->query("bunch/zhongcheng") + "%");
                }

                if (n < 1)
                        return notify_fail(arg + "����û���κε��̡�\n");

                msg += "\nĿǰ" + HIM + fam + NOR + "����" + HIM + chinese_number(n) + NOR + "�����̡�\n";
                msg += HIY "������������������������������������������������������������������������������������������\n" NOR;
        
                write(msg);
        me->start_busy(2);
                return 1;
        }
        
        area = environment(me);
        
        if (arg != area->short())
                return notify_fail("����뵽ʵ�ز��ܽ��п�����\n"); 
                
        if (! area->is_area_room() || ! area->query("area/ziyuan")) 
                return notify_fail("���ﲻ���ڰ��ɿɿ������̣�\n"); 
                         
        if (area->query("bunch/bunch_name") != fam) 
                return notify_fail("���ﲻ������İ��ɵ��̣����ʲô������\n"); 

        if (area->query("bunch/npc_id")) 
                npc = present(area->query("bunch/npc_id"), environment(me)); 
                
        if (! objectp(npc) || (string)npc->query("bunch/area_file") != base_name(environment(npc))) 
                return notify_fail("����" + arg + "�����ģΣУò�δ��λ���޷����п�����\n"); 

        kaifa = area->query("bunch/kaifa");
        money = kaifa * 10000;
        
        if ((int)me->query("balance") < money)     
        {
                return notify_fail("�����ϵ�Ǯ����������" + arg + "����Ҫ" +
                                   MONEY_D->money_str(money) + "��\n");
        }
        
        me->add("balance", -money);
        me->save();
        
        if (kaifa < 100) area->set("bunch/kaifa", kaifa + 1);
        else return notify_fail(arg + "�Ŀ������Ѵﵽ��󣬲����ٿ�����\n");
     
        area->save();
        me->start_busy(2);
        write("�㻨����" + MONEY_D->money_str(money) + "����" + arg + "��" + arg + "�Ŀ�����������һ�㣡\n");
        return 1;
}
        
int help(object me)
{
        write(@HELP

ָ���ʽ��kaifa [��������]

���ڿ�������е��̣����Ӱ�����롣

HELP
        );
        return 1;
}


