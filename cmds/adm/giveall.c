// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// giveall.c

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object ob;
        int count;
        string target, gift_file, str;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
                
        if (! arg)  
                return notify_fail("giftall �������������ң������ʽ�� giftall </·��/../Ŀ���ļ���> <����>\n\n"); 
    
        if (sscanf(arg, "%s %d", target, count) != 2) 
                target = arg;   
        
        if (sscanf(target, "%*s.c") != 1)
                target += ".c";
        gift_file = target; 
        
        if (file_size(gift_file) == -1)
                return notify_fail("·������ȷ���޷��ҵ���Ʒ��\n");
        
        seteuid(getuid());

        foreach(object player in users())
        {
                ob = new(target); 
                
                if (count > 1 && ob->query("base_unit")) 
                        ob->set_amount(count); 
                        
                ob -> move(player); 
                
                tell_object(player, HIW "\n\n��Ȼ�Ӽ��߼�Զ������м��ٽ���һֻ���������"HIR"���"HIW"��������ҫ�߲ʹ�â��\n" NOR);
                tell_object(player, HIC "��צ���ƺ�ץ��ʲô������ͻȻ"HIC"���"HIW"�ɿ���צ���и�����ֱ�������������\n" NOR);
                tell_object(player, HIG "����һ��������һԾ�ɸ߽�����ץ�����У���������Ʈ����档\n\n" NOR);
        
        }
        str = sprintf("���� %d λ��ҵõ���%s��\n\n", sizeof(users()), target->query("name"));    
        me->start_more(str);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��giveall ��Ʒ·��

�����ߵ��������һ����Ʒ��
HELP
        );
        return 1;
}
