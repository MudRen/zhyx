#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "����" NOR, ({ "dragon horn", "horn" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�����ǣ���ϡ���䱦��\n" NOR);
                set("unit", "��");
                set("value", 800000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}