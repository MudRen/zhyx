#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(YEL "阿发日记" NOR, ({ "afrji" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本阿庆嫂的儿子阿发以前的日记．\n");
          }

    setup();
}

