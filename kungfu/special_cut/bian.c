// bian.c �����ѧ
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "�����ѧ" NOR; }

int perform(object me, string skill, string arg)
{
        int i;
      
        object ob;

        if (time() - me->query("special/bian") < 600)
                return notify_fail("���ʩչ������ѧ��������˵�ɣ�\n");

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ���������ĸ�ʽ�д���\n"
                                   "��ʽ �� special bian <����id> \n");


        if (! playerp(ob))return notify_fail("�����ѧֻ�ܶ�ͬ�����ʹ�ã�\n");

        if (ob->query("family/family_name") != me->query("family/family_name"))
                return notify_fail("�����ѧֻ�ܶ�ͬ�����ʹ�ã�\n");

        message_vision(HIM "$N" HIM "ʩչ�������ѧ�����֮�������ڶ� ����\n" NOR, me);
        
        if ((int)me->query("family/gongji")< 10000)
                me->add("family/gongji", 900 + random(500));
        me->start_busy(2);

        tell_object(me, HIG "������ɹ�������ˣ�\n");

        me->set("special/bian", time());

        return 1;
}

