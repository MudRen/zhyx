#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "����֮��" NOR, ({ "phenix vein", "vein" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ�����˵Ľ��Ө͸����\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
