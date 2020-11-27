// hua4.c

inherit ITEM;
inherit F_FOOD; 

#include <ansi.h>

void create()
{
	set_name(HIC "翡翠兰" NOR, ({"feicui lan", "feicui", "lan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "朵");
		set("long", "这是一朵千年难得一见的翡翠兰，据说能解百毒。\n");
        	set("value", 1000000);
                set("food_remaining", 20); 
                set("food_supply", 500); 
	}
        setup();
}