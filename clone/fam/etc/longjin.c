#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "����" NOR, ({ "dragon vein", "vein" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ������������⡣\n" NOR);
                set("unit", "��");
                set("value", 400000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}