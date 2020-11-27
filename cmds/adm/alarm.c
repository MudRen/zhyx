// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// alarm.c

#include <ansi.h>
inherit F_CLEAN_UP;

#define SHOUT_LIST      ({ })

int help(object me);
void create() {seteuid(getuid());}


int main(object me, string arg)
{
        object ob;
        string target, msg, mud,from;
        object obj;

        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;
                        
        if (! arg || sscanf(arg, "%s %s", target, msg) != 2) 
                return help(me);
                
        obj = find_player(target);
        write(HIG "\n �㾯��" + obj->name(1) + "������" + msg + "����Ϊ�� \n" NOR);
        
        tell_object(obj, sprintf( HIR "\n ��Ϸ�����߾����㣺\n \n \n \n" + "      ���" HIW "��%s��" HIR "��ΪΥ������Ϸ����������"HIW" help rules "HIR"��ѯ��Ϸ�����ش˾��档\n \n"+"      �����κ����⣬���������ߡ������ٷ��������չ�����\n \n \n \n \n \n" NOR, msg));

        if (! wizardp(me) && member_array(me->query("id"), SHOUT_LIST) == -1)
                return notify_fail("Ŀǰ�ݲ�������� shout��\n");
                
        if (! arg) return notify_fail("����Ҫ���ʲô��\n");

        shout( HIG "��ϵͳ��Ϣ��ϵͳ���棺"+ obj->name(1) + "��Ϊ" + msg + "��ϵͳ���档\n" NOR );
        write( HIG "��ϵͳ��Ϣ��ϵͳ���棺"+ obj->name(1) + "��Ϊ" + msg + "��ϵͳ���档\n" NOR );

        return 1;
}




int help(object me)
{
        write(@HELP
ָ���ʽ��alarm <ĳ��> <ѶϢ>
����������ָ���Υ���������ҡ�
ͬʱ���ɱ������������ֱ�Ӵ���Υ����ҵ�Ȩ����
HELP
        );
        return 1;
}

