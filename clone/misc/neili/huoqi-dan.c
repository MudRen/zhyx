#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "������" NOR, ({"huoqi dan", "huoqi", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 50000);
                set("only_do_effect", 1);
                set("long", HIY "һ����ɫ��ҩ�衣�ָ�2000��������\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if (time() - me->query_temp("last_eat") < 2)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        me->set_temp("last_eat", time());

        message_vision(HIW "$N����һ�Ż��������е������������䡣\n" NOR, me);

        if (me->query("max_neili") - me->query("neili") < 2000)
                  me->set("neili", me->query("max_neili"));
        else
                  me->add("neili", 2000);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}
