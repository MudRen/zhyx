// meigui.c

#include <ansi.h> 
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(HIR"õ�廨"NOR, ({ "mei gui", "hua", "gui" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ������Ư����õ�廨��\n");
                set("value", 300);
                set("material", "steel");

        }
        init_blade(50);
        setup();
}

