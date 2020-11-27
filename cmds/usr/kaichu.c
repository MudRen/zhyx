// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string bunch;

        if (! arg || arg == "")
                return notify_fail("ָ���ʽ��kaichu <���id>\n");
                
        if (! stringp(bunch = me->query("bunch/bunch_name")))
        {
                write("�����ڻ�û�м����κΰ����ء�\n");
                return 1;
        }
        
        if (me->query("bunch/level") != 9)
        {
                write("ֻ�а�������Ȩ������ĳ�˳���ᣡ\n");
                return 1;
        }
        
        if (arg == me->query("id"))
        {
                write("�����Լ����㻹�����ɢ��İ��ɣ�\n");
                return 1;
        }        

        if (! objectp(ob = find_player(arg)))
        {
                ob = UPDATE_D->global_find_player(arg);

                if (! objectp(ob))
                { 
                        write("û�������ҡ�\n");
                        return 1;
                } 
        
                if (ob->query("bunch/bunch_name") != bunch)
                {
                        UPDATE_D->global_destruct_player(ob);                                                      
                        write("��������İ������ˣ�����Ȩ��������\n");    
                        return 1;                   
                        
                }         
        }               

        CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + ob->query("name") + "(" + arg + ")" +
                        "�����ɡ�" + bunch + "���������ˡ�");
                        
        BUNCH_D->add_bunch_fame(bunch, -ob->query("weiwang") / 2); 
        ob->add("weiwang", -ob->query("weiwang") / 10);
        
        UPDATE_D->clear_user_data(arg, "bunch");
        UPDATE_D->global_destruct_player(ob);    
        return 1;
}      
