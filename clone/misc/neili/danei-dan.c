#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "���ڵ�" NOR, ({"danei dan", "danei", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 10000);
                set("only_do_effect", 1);
                set("long", HIY "һ����ɫ��ҩ�衣�ָ�800��������\n" NOR);
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

        message_vision(HIW "$N����һ�Ŵ��ڵ����е������������䡣\n" NOR, me);

        if (me->query("max_neili") - me->query("neili") < 800)
                  me->set("neili", me->query("max_neili"));
        else
                  me->add("neili", 800);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}
