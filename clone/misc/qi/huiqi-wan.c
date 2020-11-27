
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "������" NOR, ({"huiqi wan", "huiqi", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "һ�ź�ɫ��ҩ�衣�ָ�1000����Ѫ�������Ѫ��\n" NOR);
                set("value", 30000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if (time() - me->query_temp("last_eat") < 5)
        {
                write("��ճԹ�ҩ��ҩ����û����ȫ���ա�\n");
                return 1;
        }
        me->set_temp("last_eat", time());

        message_vision(HIR "$N" HIR "����һ�Ż����裬ֻ����̩֮����\n" NOR, me);

        if (me->query("max_qi") - me->query("eff_qi") <= 1000)
        {
                 me->set("eff_qi", me->query("max_qi"));
                 if (me->query("max_qi") - me->query("qi") <= 1000)
                        me->set("qi", me->query("max_qi"));
                 
                 else 
                        me->add("qi", 1000);  
        }


        else 
        {
                me->add("eff_qi", 1000);
                me->add("qi", 1000);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
