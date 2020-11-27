// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *member;
        string bunch;
        string id;
        object area, npc;
        string msg;
        int n;
                
        if (me->is_busy()) return notify_fail("����æ���أ�\n");
                
        if (! arrayp(member = BUNCH_D->query_area_fame()))
        {
                write("�����л�Ӣ��û���κε��̿ɱ��������á�\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail("�л�Ӣ������û���κε��̿ɱ��������á�\n");

        msg = sprintf(HIC "\n%-16s%-12s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR,
                      "��������", "��������", "פ�أΣУ�", "�ʽ��", "������",
                      "�ʲ����ƽ�", "�������루������", "�ҳ϶�");
                      
        msg += HIY "������������������������������������������������������������������������������������������������������\n" NOR;
                
        n = 0;
        foreach (id in member)
        {
                area = get_object(id);
                if (! objectp(area))
                        continue;
                        
                bunch = area->query("bunch/bunch_name");
                
                // npc = get_object(area->query("bunch/npc_file"));
                
                n++;
                msg += sprintf(HIC "%-16s%-12s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR, 
                               area->short(), stringp(bunch) ? bunch : "�� �� ��",
                               area->query("bunch/npc_name") + "(" + area->query("bunch/npc_id") + ")",
                               area->query("area/ziyuan") ? area->query("bunch/jizhi") + "%" : "----", 
                               area->query("area/ziyuan") ? area->query("bunch/kaifa") + "%" : "----", 
                               area->query("bunch/money") / 10000 + " ��", 
                               area->query("bunch/last_money") / 100 + " ��",
                               (stringp(bunch) && bunch == me->query("bunch/bunch_name")) ? 
                               area->query("bunch/zhongcheng") + "%" : "------"); 
        }

        if (n < 1)
                return notify_fail("�����л�Ӣ��û���κε��̿ɱ��������á�\n");

        msg += "\nĿǰ�л�Ӣ�۹���" + HIM + chinese_number(n) + NOR + "�����̡�\n";
        msg += HIY "������������������������������������������������������������������������������������������������������\n" NOR;
        
        write(msg);
        me->start_busy(2);
        return 1;
}
        
int help(object me)
{
        write(@HELP
ָ���ʽ��dipan
������ʾ�л�Ӣ�����е��̵�����������ϡ�
HELP
        );
        return 1;
}



