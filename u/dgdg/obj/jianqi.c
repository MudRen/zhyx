#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW "剑气" NOR, ({ "jian qi", "jian", "qi" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("long", HIW "这是一束由内力化成的剑气。\n" NOR);
                set("value", 0);
                set("material", "air");
                set("power", 1000000);
        }
        init_sword(query("power"));
        setup();
}
