#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "鸡毛信" NOR, ({ "jimao letter", "jimao", "letter"}) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long", "一封信，信的封口处插了一根鸡毛。\n" );
                set("value", 1);
        }
}

int is_container() { return 1; }


