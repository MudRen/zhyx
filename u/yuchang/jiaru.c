// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

string *swear_msg = ({
    HIY "�������ϣ�������λ�����ڽ��ճ�����ᣬ������ҵ��\n" NOR,
    HIY "�Խ������ֵ��Ǹε����գ������빲�� \n" NOR,
    HIY "�и�ͬ������ͬ���� \n" NOR,
    HIY "����ͬ��ͬ��ͬ����������ͬ��ͬ��ͬ������\n" NOR,
    HIY "ף���ֵ�������ͬ�ԣ�����ع��٣�\n" NOR,
    HIY "��Υ���ģ�������� \n" NOR,
    HIY "��Υ���ģ�������� \n" NOR,
    HIY "��Υ���ģ�������� \n" NOR,
});
int main(object me, string arg)
{
        object ob;
        object *who;
        int num;
        int stage;
        string bunch;
	string str, str1, str2;
        if (! arg || arg == "")
                return notify_fail("��Ҫ����˭�İ�᣿\n");

        if (me->query("combat_exp") < 1000)
                return notify_fail("��ų��뽭������ĥ��ĥ���ɡ�\n");    
                                         
        if (stringp(bunch = me->query("bunch/bunch_name")) ||
            stringp(bunch = me->query("league/league_name")))
                return notify_fail("��Ǹ�����Ѿ��ǡ�" + bunch + "�������ˣ��޷�����������ᡣ\n");
                
        if (me->is_fighting() || me->is_busy())
                return notify_fail("����æ���ء�\n");
                
        if (me->query("id") == arg)
                return notify_fail("��û����ô����\n");
                
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("���û����ô���ˡ�\n");
                
        if ((object)me->query_temp("invite/target") != ob)
                return notify_fail("��Ǹ��" + ob->query("name") + "��û��������μ����İ�ᡣ\n");
                
        if (! stringp(bunch = ob->query("bunch/bunch_name")))
                return notify_fail("��Ǹ��" + ob->query("name") + "���ڲ������κΰ�ᣡ\n");                           

        BUNCH_D->add_member_into_bunch(bunch, me->query("id"));
        BUNCH_D->add_bunch_fame(bunch, me->query("weiwang") / 10); 
        me->set("bunch/time", time());
        me->set("bunch/bunch_name", bunch);
        me->set("party/right", 5);
        me->set("bunch/title", "����");
                        
	message_vision(HIR "$N�泯������ϥ���£���ȭ��ü��ׯ�ط��ģ�" + swear_msg[stage++] + "\n", who[num++]);
        message("channel:rumor", HIM "����Ұ�᡿ĳ�ˣ�" + me->query("name") + 
                                 "(" + me->query("id") + ")�����ᡸ" + bunch + 
                                 "��������Ϊ��" + bunch + "��Ч����\n" NOR, users());
                                 
        me->delete_temp("invite/target");
        
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��join | jiaru <ĳ��>
���ָ����������ĳ�˵İ�ᡣǰ����ĳ�˱��������㡣

���ָ�invite
HELP
        );
        return 1;
}



