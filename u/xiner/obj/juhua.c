#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(MAG "野菊花" NOR, ({ "ye juhua", "juhua" }));
        set("weight", 100);
        if (clonep())
                set_default_object(__FILE__);
        else {
		set("value", 100);
                set("long",HIG "一朵很难见到的野菊花，尽管已经过摘下来很长时间了依然有一股淡淡的香味。\n" NOR);
                set("unit", "朵");
                set("material", "wood");
        }
        setup();
}       


