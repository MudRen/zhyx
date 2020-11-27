#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "��һ��" NOR, ({ "wuyi jindan", "jindan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "��һ����𵤣������츳����һ�㡣\n" NOR);
                set("unit", "��");  
                set("no_sell", 1);
                set("weight", 200);  
                set("only_do_effect", 1);
                set("gift_point",110);
        }
}

int do_effect(object me)
{

        message_vision(WHT "$N" WHT "һ������������һ" +
                          query("unit") + name() + WHT 
                       "��\n" NOR, me);

        if ( me->query("liwu/wuyi2005/eat") )
        {
                tell_object(me, HIR "�����������ҩ����û��ʲô"
                                "���á�\n" NOR);
        } else
                // ������Ӧ���츳����
{
        if (me->query("gift/str/succeed") + me->query("gift/str/fail") <= 9)
        {
                me->add("str", 1);
                me->add("gift/str/succeed", 1);
                me->add("gift/str/all", 1);
                tell_object(me, HIR "����������������ˣ����ø������ˣ�\n" NOR);   
        }
        if (me->query("gift/int/succeed") + me->query("gift/int/fail") <= 9) 
        {
                me->add("int", 1);
                me->add("gift/int/succeed", 1);
                me->add("gift/int/all", 1);
                tell_object(me, HIW "����������������ˣ����ø������ˣ�\n" NOR);  
        }
        if (me->query("gift/con/succeed") + me->query("gift/con/fail") <= 9) 
        {
                me->add("gift/con/succeed", 1);
                me->add("gift/con/all", 1);
                me->add("con", 1);
                tell_object(me, HIY "���������������ˣ����ø�ǿ׳�ˣ�\n" NOR);  
        }
        if (me->query("gift/dex/succeed") + me->query("gift/dex/fail") <= 9) 
        {
                me->add("dex", 1);
                me->add("gift/dex/succeed", 1);
                me->add("gift/dex/all", 1);
                tell_object(me, HIM "��������������ˣ����ø�����ˣ�\n" NOR);
        }
         me->set("liwu/wuyi2005/eat",1);
         log_file("static/wuyi", sprintf("%s(%s) eat �츳 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));
}
        destruct(this_object());

        return 1;
}


