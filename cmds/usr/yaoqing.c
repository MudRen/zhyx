// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit F_CLEAN_UP;

#include "/adm/npc/npcneed.h"

int main(object me, string arg)
{
        object ob, *target;
        string bunch;
        int money, i, flag;
        mapping data;
        string *what, stuffid, stuffname;

        if (! arg || arg == "")
                return notify_fail("��Ҫ����˭������İ�᣿\n");
                        
        if (! stringp(bunch = me->query("bunch/bunch_name")))
                return notify_fail("��û�вμ��κΰ�ᣬ�޷��������˼��롣\n");               
        
        flag = 0;
        
        if (intp(me->query("bunch/level")) &&
            (int)me->query("bunch/level") > 5)
                flag = 1;                       
                        
        if (me->query("id") == arg)
                return notify_fail("�����Լ�����\n");
                
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����û��ô���ˡ�\n");
                
        if (! ob->is_character())
                return notify_fail("��ֻ�����롸�ˡ�������İ�ᡣ\n");
                
        if (ob->query("bunch/bunch_name") == me->query("bunch/bunch_name"))
                return notify_fail(ob->query("name") + "�Ѿ��Ǳ�������ˡ�\n");
                
        if (me->is_fighting() || me->is_busy())
                return notify_fail("����æ���ء�\n");
                
        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("�Է���æ���ء�\n");
                
        if (! living(ob)) return notify_fail("�����Ū������˵��\n");       
                
        if (playerp(ob) && ! flag)
                return notify_fail("����Ȩ������Ҽ��롸" + bunch + "����\n");

        message_vision("$N����$n�μӰ�ᡸ" + bunch + "����\n", me, ob);
        
        if (! playerp(ob))        
        {
                if (! ob->query("bunch/zhengzhao") || ! ob->is_bunch_npc())
                        return notify_fail("������" + ob->query("name") +
                                "����İ��û����Ȥ��\n");
                                
                if (sizeof(BUNCH_D->query_npcs(bunch)) > BUNCH_D->query_bunch_fame(bunch) / 500000)
                        return notify_fail("������İ�������������������" + ob->query("name") +
                                "����İ��û����Ȥ��\n");
                                
                switch (ob->query("bunch/zhengzhao"))  
                {
                case 1: 
                        if ((! stringp(bunch = ob->query("bunch/bunch_name")) ||
                            ob->query("bunch/zhongcheng") < me->query("meili")) &&
                            ob->query("qi") * 100 > ob->query("max_qi") * 80) 
                        {
                                message_vision("$N��$n˵������������ˣ����Ҳ����д�(qiecuo)һ���书��Σ���\n",
                                               ob, me);
                                ob->set_temp("invite/target", me);
                                return 1;
                        }
                        message_vision("$N����$nЦ�������ҿɲ��Ҹ��ʹ�ﰡ����\n", ob, me);
                        return 1;
                        
                case 2: 
                        if (! (bunch = ob->query("bunch/bunch_name")) ||
                            ob->query("bunch/zhongcheng") < me->query("meili"))    
                        {
                                money = ob->query("combat_exp") / 1000;
                                
                                if (money < 1) money = 1;
                                
                                money = money * 1000;
                                message_vision("$N���ٺ١��˼�������$n������" +
                                               chinese_number(money / 1000) + "���ƽ���һ����Ҳ���С����\n",
                                               ob, me);
                                ob->set_temp("invite/target", me);
                                ob->set_temp("invite/money", money);
                                return 1;
                        }
                        message_vision("$N����$nЦ�������ҿɲ��Ҹ��ʹ�ﰡ����\n", ob, me);
                        return 1;
                        
                case 3: 
                        if (! (bunch = ob->query("bunch/bunch_name")) 
                        ||  ob->query("bunch/zhongcheng") < me->query("meili"))    
                        {
                                data = ob->query_temp("invite/target");
                                
                                if (! mapp(data)) data = ([]);
                                
                                target = keys(data);
                                
                                if (member_array(me->query("id"), target) != -1) 
                                {
                                        sscanf(data[me->query("id")], "%s:%s", stuffid, stuffname);
                                        message_vision("$N��$n���������Ҳ���˵�����𣿰�" +
                                                       stuffname + "(" + stuffid + ")����������\n",
                                                       ob, me);
                                        return 1;
                                }
                                
                                if (sizeof(target) >= 4)           
                                {
                                        message_vision("$NЦ�������ɴ�ҿ�����" +
                                                       RANK_D->query_respect(ob) + "��ʤ�м���\n",
                                                       ob);
                                        return 1;
                                }
                                
                                what = keys(npcneed);
                                stuffid = what[random(sizeof(what))];
                                stuffname = npcneed[stuffid];
                                data[me->query("id")] = stuffid + ":" + stuffname;
                                ob->set_temp("invite/target", data);
                                message_vision("$N����$n����ֻҪ������������֮�ڰ�" +
                                               stuffname + "(" + stuffid + ")" +
                                               "����������һ�к�������\n",
                                               ob, me);
                                               
                                // remove_call_out("delete_target");
                                call_out("delete_target", 180, ob, me->query("id"));
                                return 1;
                        }
                        message_vision("$N����$nЦ�������ҿɲ��Ҹ��ʹ�ﰡ����\n", ob, me);
                        return 1;
                }
        } else    
        {
                tell_object(ob, "�����Ը�����Է��İ�ᣬ��ʹ�� jiaru " + me->query("id") + "��\n");
                ob->set_temp("invite/target", me);
                return 1;
        }
}

void delete_target(object npc, string name)
{
        mapping data;
        
        if (! objectp(npc)) return;
        
        data = npc->query_temp("invite/target");
        
        if (! mapp(data))   return;
        
        map_delete(data, name);
        npc->set_temp("invite/target", data);
}


int help(object me)
{
        write(@HELP
ָ���ʽ��invite | yaoqing <ĳ��>
���ָ����������ĳ�˼�����İ�ᡣĳ�˿�������һ��ǿ����еģΣУá�
ע�⣺������Ҽ����ᣬ��������ڰ����������ݵ��ˡ�

���ָ�join
HELP
        );
        return 1;
}



