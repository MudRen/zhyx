// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int i;
        if (! (string)me->query("bunch/bunch_name"))
                return notify_fail("��û�вμ��κΰ�ᣬ�޷�ͨ�������书����NPC��\n");
                
        if (! arg)
                return notify_fail("��Ҫ��˭�д��书��\n");
                
        if (! ob = present(arg, environment(me)))
                return notify_fail("���û����ô���ˡ�\n");
                
        if (! ob->is_character())
                return notify_fail("��������ǲ����Ǹ����\n");
                
        if (playerp(ob))
                return notify_fail("��ֻ����NPC�����书��\n");
                
        if (! living(ob)) return notify_fail("����Ȱ���Ū����˵��\n");
        
        if (me->is_fighting() || me->is_busy())
                return notify_fail("����æ���ء�\n");
                
        if ((int) ob->query("bunch/zhengzhao") != 1)
                return notify_fail("���NPC�������д��书�ķ�ʽ���С�\n");
                
        if ((string)ob->query("bunch/bunch_name") == me->query("bunch/bunch_name"))
                return notify_fail("���NPC�Ѿ��Ǳ����ֵܣ�����ͨ�������书�����С�\n");
                
        if ((object)ob->query_temp("invite/target") != me)
                return notify_fail("�����Ҫ������(yaoqing)���NPC��\n");
                
        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("�Է���æ���ء�\n");
                
        if ((string)ob->query("bunch/bunch_name") && ob->query("bunch/zhongcheng") > me->query("meili"))
                return notify_fail("�����ӶԷ���������������ա�\n");
                
        if (ob->query("qi") * 100 < ob->query("max_qi") * 80)
                return notify_fail("�����ӶԷ���������������ա�\n");
                
        message_vision(HIY"$N���������" + RANK_D->query_self(ob) +
                       "�ұ����" + me->query("name") + "�ĸ��У���\n"NOR,
                       ob, me);
                       
        if (ob->query_temp("invite/target"))  
                ob->delete_temp("invite/target");
                
        me->fight_ob(ob);
        ob->fight_ob(me);
        remove_call_out("check_qi");
        call_out("check_qi", 0, me, ob);
        return 1;
}

void check_qi(object me,object ob)
{
        object lp_me, lp_npc;
        
        if (! objectp(me) || ! objectp(ob)) return;
        
        if (! me->query("bunch/bunch_name")) return;
        
        if (me->is_fighting(ob))
        {
                call_out("check_qi", 1, me, ob);
                return;
        }
        
        if (! environment(ob))   return;
        
        if (environment(me) != environment(ob))    return;
        
        if (ob->query("qi") > ob->query("max_qi") / 2)     
        {
                message_vision("$N����һЦ������$n����������" + RANK_D->query_respect(me)
                               + "���ÿ������а�����\n", ob, me);                
        }
        
        else if (ob->query_last_damage_from() != me) 
        {
                message_vision("$N����һ�������������˰�æ��ʲô��˼����\n",ob);
        }
        else            
        {
                message_vision("$N��$nһ��ȭ������" + RANK_D->query_respect(me)
                               + "��Ȼ������" + RANK_D->query_self(ob)
                               + "����ý�������\n", ob, me);
                ob->do_join_bunch(me);
        }
}


