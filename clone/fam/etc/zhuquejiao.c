#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "����֮��" NOR, ({ "phenix horn", "horn" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ������֮�ǣ�ͨ����졣\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
