// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string banghui;
        object ob;
        
        seteuid(getuid()); 
        
        if (! stringp(me->query("bunch/bunch_name")) || (int)me->query("bunch/level") != 9)
                return notify_fail("ֻ�а��İ�������ʹ������ָ�\n");
                
        banghui = me->query("bunch/bunch_name");
        
        if (me->is_fighting() || me->is_busy())
                return notify_fail("����æ���ء�\n");
                
        if (! arg)
                return notify_fail("��Ҫ��λ��˭��\n");
                
        if (me->query("id") == arg)
                return notify_fail("��λ���Լ����б�Ҫ��\n");
                
        if (! ob = present(arg, environment(me)))
                return notify_fail("���û����ô����ҡ�\n");
                
        if (! playerp(ob))
                return notify_fail("��ֻ����λ����ҡ�\n");
                
        if (ob->query("bunch/bunch_name") != banghui)
                return notify_fail("��ֻ����λ����������ҡ�\n");
                
        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("�Է���æ���ء�\n");                
        
        BUNCH_D->set(banghui + "/bangzhu", ob->query("id"));
        BUNCH_D->save();
        
        ob->set("bunch/level", 9);
        ob->set("bunch/title", "����");
        me->set("bunch/title", "�ϰ���");
        me->set("bunch/level", 10);
        ob->save();
        me->save();
        message_vision("$N����ᡸ" + banghui + "���İ���֮λ��λ����$n��\n", me, ob);
        return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ��rangwei <ĳ��>
���ָ��Ϊ����ר�ã�����������֮λ��λ�����ˡ�
ǰ����ĳ�˱���Ϊ������ڡ�
HELP
        );
        return 1;
}


