
//����(��10��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "����" NOR, ({ "chunjuan", "roll" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�����ڲ��ܳԵ��Ĵ���������ֱ����ˮ��\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);
             }
        setup();
}

void init()
{
     add_action("do_eat","eat");
}

int do_eat(string arg)
{
        object me;
        int year, *date;
        date = localtime(time());
        year = date[5];

        me = this_player();

        if (!arg || (arg != "chunjuan" &&
                     arg != "roll"))
                return 0;

        if (me->query("reward/gift/chunjuan/" + year))
        {
                write(HIR "���Ѿ��Թ�����Ĵ����ˣ���Ի�����������!\n" NOR);
                return 1;
        }

        me->set("reward/gift/chunjuan/" + year, 1);
        message_vision(HIW "$N" HIW "������һ�����ˡ�\n" NOR, me);

        me->add("potential", 100000);

        tell_object(me, HIG "��ϲ��������ʮ���Ǳ�ܡ�"
                            "��л��Ա�վ��֧�֣�ף���´����֣�\n" NOR);
        destruct(this_object());
        return 1;
}

int query_autoload()
{ return 1; }
