// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string bunch, someone;
        int amount;
        int money;
        object ob;
        object area;
        
        if (! arg) return notify_fail("��ʹ��help tisheng���鿴�����\n");

        if (! stringp(bunch = me->query("bunch/bunch_name")))
                return notify_fail("��û�вμ��κΰ�ᣬ�޷������κΣΣУá�\n");
                        
        if (sscanf(arg, "%d %s", amount, someone) != 2)
                return notify_fail("��ʹ��help tisheng���鿴�����\n");                

        if (amount < 0 || amount > 10)
                return notify_fail("ÿ��������ֵ����С����Ҳ���ܴ���ʮ�㡣\n");
                                
        if (! ob = present(someone, environment(me)))
                return notify_fail("���û����ô���ˡ�\n");
                                
        if (! ob->is_character())
                return notify_fail("����������������\n");
                
        if (playerp(ob))
                return notify_fail("��ֻ����������ΣУð��ڵļ��ܡ�\n");
                
        if (! living(ob))
                return notify_fail("����Ȱ�" + ob->query("name") + "Ū����˵��\n");
             
        if (me->is_fighting() || me->is_busy())
                return notify_fail("����æ���ء�\n");
                
        if (ob->is_fighting() || ob->is_busy())
                return notify_fail(ob->query("name") + "��æ���ء�\n");

        if (bunch != (string)ob->query("bunch/bunch_name"))
                return notify_fail("��ֻ������������ڵģΣУð��ڡ�\n");
                
        if (! ob->is_bunch_npc())
                return notify_fail(ob->query("name") + "�ƺ����ڲ���������������\n");
                
        area = environment(ob);

        if (! area->is_area_room() || 
            area->query("bunch/bunch_name") != bunch ||
            area->query("bunch/npc_file") != base_name(ob))                                                           
                return notify_fail(ob->query("name") + "�ƺ����ڲ���������������\n");

        if ((int)area->query("bunch/zhongcheng") >= (int)ob->query("bunch/max_zhongcheng"))
                return notify_fail(ob->query("name") + "���ҳ϶��Ѿ��ﵽ��󣬲���Ҫ���������ˡ�\n");

        money = amount * 10000;
                
        if ((int)me->query("balance") < money)     
                return notify_fail("�����ϵ�Ǯ������" + ob->query("name") +
                                   "���ҳ϶�ÿ����һ����Ҫһ���ƽ�\n");
                                
        me->add("balance", -money);
        me->save();
                
        if ((int)area->query("bunch/zhongcheng") + amount >= (int)ob->query("bunch/max_zhongcheng"))
        {
                area->set("bunch/zhongcheng", (int)ob->query("bunch/max_zhongcheng"));
                ob->set("bunch/zhongcheng", (int)ob->query("bunch/max_zhongcheng"));
        } else    
        {
                area->add("bunch/zhongcheng", amount);
                ob->add("bunch/zhongcheng", amount);
        }
                
        area->save();
        me->start_busy(1);
        write("�㻨�� " + money / 10000 + " ���ƽ𣬽�" + ob->query("name") + "���ҳ϶�������" + amount + "�㣡\n");

        return 1;
}


int help(object me)
{
        write(@HELP

ָ���ʽ��tisheng <amount> <id>

����ָ��������������������NPC���ҳ϶�(zhongcheng)������������ĳ��
NPC��Ϊ���������ս�������ҳ϶ȣ���Ҫ������Ǯ�������������
HELP
        );
        return 1;
}



