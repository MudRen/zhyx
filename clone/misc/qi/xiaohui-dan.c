
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "С�ص�" NOR, ({"xiaohui dan", "xiaohui", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "һ�ź�ɫ��ҩ�衣�ָ�300����Ѫ�������Ѫ��\n" NOR);
                set("value", 2000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if (time() - me->query_temp("last_eat") < 2)
        {
                write("��ճԹ�ҩ��ҩ����û����ȫ���ա�\n");
                return 1;
        }
        me->set_temp("last_eat", time());
        message_vision(HIR "$N" HIR "����һ��С�ص���ֻ����̩֮����\n" NOR, me);

        if (me->query("max_qi") - me->query("eff_qi") <= 300)
        {
                 me->set("eff_qi", me->query("max_qi"));
                 if (me->query("max_qi") - me->query("qi") <= 300)
                        me->set("qi", me->query("max_qi"));
                 
                 else 
                        me->add("qi", 300);  
        }


        else 
        {
                me->add("eff_qi", 300);
                me->add("qi", 300);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
